*This project has been created as part of the 42 curriculum by kaisuzuk, ketomita.*

# Description
ft_irc is an IRC server implemented in C++98.

The goal of this project is to deepen understanding of socket communication, I/O multiplexing, and network programming by reading and implementing the IRC protocol specification.
You can connect and verify operation using a standard IRC client.
In this project, we used the `nc` command for testing.

## What is IRC?

IRC (Internet Relay Chat) is a text-based real-time communication protocol developed in 1988. Clients connect to a server and can engage in group chats or private messaging through rooms called channels.

![Basic IRC architecture](assets/architecture1.png) <br>
*Image source: [Internet Relay Chat — The UChicago χ-Projects](http://chi.cs.uchicago.edu/chirc/irc.html)*

Channels exist as long as there are participants, and the first client to join becomes the operator.
Operators are considered the owners of the channel and can perform the following operations:
- Kick participants from the channel (KICK)
- Change channel modes (MODE)
- Grant operator privileges to other clients

A single message is a string of up to 512 characters. Messages are delimited by a CR-LF (Carriage Return - Line Feed) pair (i.e., `\r\n`). Since this delimiter is included in the 512-character limit, there are only 510 characters of usable space per message.
A message consists of two parts: a command and command parameters.
Commands and parameters are all separated by a single ASCII space character.
The following are examples of valid IRC messages:

```text
NICK amy

JOIN #tradis

MODE amy +o
```

If the last parameter begins with a colon character, the value of that parameter is the remainder of the message (including space characters), meaning it is treated as a single parameter.
```text
PRIVMSG roy :hey Rory...

PRIVMSG #cmsc23300 :Hello everybody

QUIT :Done for the day, leaving
```


## Socket
The Internet uses a communication protocol called TCP/IP. To use TCP/IP from a program, a special gateway is needed to bridge the world of the program and the world of TCP/IP. That gateway is the socket.

When sending and receiving data through a socket, you can do so in the same way as file I/O. That is, writing data you want to send to a socket delivers it to the socket of the communicating computer. Receiving data means reading it from the socket. The OS handles the actual data transmission and reception.

### Socket Types
```text
SOCK_STREAM     -> TCP (reliable, ordered, connection-oriented)
SOCK_DGRAM      -> UDP (unreliable, unordered, connectionless)
```

### Server-side Flow
```bash
# 1. Create socket
int fd = socket(AF_INET, SOCK_STREAM, 0);

# 2. Bind a name to the socket (associate with port)
## Set port etc. in addr
bind(fd, (struct sockaddr*) &addr, sizeof(addr));

# 3. Start listening for connections
listen(fd, SOMAXCONN);

# 4. Accept incoming connections
int client_fd = accept(fd, (struct sockaddr*)&client_addr, &len);

# 5. Send and receive data
recv(client_fd, buf, sizeof(buf), 0);
send(client_fd, buf, len, 0);

# 6. Disconnect
close(client_fd);
```

### Client-side Flow
```bash
# 1. Create socket
int fd = socket(AF_INET, SOCK_STREAM, 0);

# 2. Connect to server
connect(fd, (struct sockaddr*)&addr, sizeof(addr));

# 3. Send and receive data
send(fd, buf, len, 0);
recv(fd, buf, sizeof(buf), 0);

# 4. Disconnect
close(fd);
```

## Non-blocking I/O

In conventional blocking I/O, when a system call such as `read` or `write` is invoked, program execution halts until the operation completes. For example, while waiting for data from one client, processing of all other clients becomes impossible.
With non-blocking I/O, system calls return immediately without blocking. This means that even when no data has arrived, other processing can continue. As a result, it becomes possible to handle multiple clients simultaneously within a single process.

However, implementing non-blocking I/O with a simple loop does not typically work as expected.
If the loop interval is long, the application will be slow to react to I/O events, which may be unacceptable. Conversely, if the loop interval is short, the application enters a busy-wait state, wastefully consuming CPU resources.
The solution to this problem is I/O multiplexing.


## I/O Multiplexing

With I/O multiplexing, you can specify multiple file descriptors and monitor whether any of them have become ready for I/O. This allows you to process only the file descriptors that are ready, without blocking, while efficiently handling multiple clients and avoiding busy-wait.

I/O multiplexing can be achieved using two essentially equivalent system calls: `select` and `poll`. In addition, there is `epoll`, which is Linux-specific. Each system call has the following characteristics.

### select
```bash
int select(int nfds, fd_set *readfds, fd_set *writefds,
           fd_set *exceptfds, struct timeval *timeout);
```
- Manages file descriptors using `fd_set` (a bitset).
- There is an upper limit on the number of file descriptors that can be monitored.
- Monitored file descriptors are specified in `fd_set` before the call. On return, the contents of `fd_set` are modified so that only file descriptors judged to be I/O-ready remain. Therefore, when called repeatedly in a loop, `fd_set` must be reinitialized each time.
- To check results, all file descriptors must be iterated (linear scan required).

### poll
```bash
int poll(struct pollfd *fds, nfds_t nfds, int timeout);

struct pollfd {
    int   fd;         /* file descriptor */
    short events;     /* requested events */
    short revents;    /* returned events */
};
```
- Manages file descriptors using a struct. When an event is notified, a bit is set in the struct member `revents`.
- No upper limit on the number of file descriptors that can be monitored.
- To check results, the struct array must be iterated (linear scan required).

### epoll
```bash
int epoll_create1(int flags);
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
int epoll_wait(int epfd, struct epoll_event *events,
               int maxevents, int timeout);
```
- No upper limit on the number of file descriptors that can be monitored.
- Only file descriptors with events are returned, so no linear scan is needed.
- `epoll_create1` creates an instance, `epoll_ctl` registers/modifies/removes monitored fds, and `epoll_wait` blocks until an event occurs.
- Linux-specific.

Based on these characteristics, `select` and `poll` do not scale efficiently as the number of monitored file descriptors increases.
Therefore, ft_irc adopts `epoll`.

## Architecture

| Class | Role |
|-----|-----|
| `FtIRCd` | Manages the entire server |
| `SocketEngine` | I/O multiplexing engine wrapping `epoll` |
| `Client` | Holds information about a connected client |
| `ClientManager` | Manages connected clients by file descriptor |
| `Channel` | Holds channel information and its participants |
| `ChannelManager` | Manages channel creation, deletion, and participants |
| `CommandParser` | Parses messages received from clients and dispatches them to the corresponding command |
| `ACommand` (+ subclasses) | Classes implementing each IRC command |
| `NumericReply` | Defines numeric replies from server to client |

## Supported Commands

| Category | Commands |
|----------|----------|
| Connection | `PASS` `NICK` `USER` `QUIT` |
| Channel | `JOIN` `PART` `KICK` `INVITE` `TOPIC` `LIST` `NAMES` |
| Messaging | `PRIVMSG` `NOTICE` |
| Mode | `MODE` (`+i`, `+t`, `+k`, `+l`, `+n`, `+o`) |
| Server | `MOTD` |

# Instructions

## Installation
```bash
git clone <project>
```

## Compilation
```bash
make            # Build
make clean      # Remove object files
make fclean     # Remove binary as well
make re         # Rebuild
```

## Running
```bash
./ircserv <port> <password>
```
| Argument | Description |
|-----|-----|
| port | Port number to listen on (1024 - 65535) |
| password | Password used by clients when connecting |

## Connecting
```bash
nc -NC localhost <port>
```

# Resources

## Books
- [TCP/IP Socket Programming in C](https://www.ohmsha.co.jp/book/9784274065194/)
- [UNIX Network Programming Vol.1](https://www.amazon.co.jp/UNIX%E3%83%8D%E3%83%83%E3%83%88%E3%83%AF%E3%83%BC%E3%82%AF%E3%83%97%E3%83%AD%E3%82%B0%E3%83%A9%E3%83%9F%E3%83%B3%E3%82%B0%E3%80%88Vol-1%E3%80%89%E3%83%8D%E3%83%83%E3%83%88%E3%83%AF%E3%83%BC%E3%82%AFAPI-%E3%82%BD%E3%82%B1%E3%83%83%E3%83%88%E3%81%A8XTI-W-%E3%83%AA%E3%83%81%E3%83%A3%E3%83%BC%E3%83%89-%E3%82%B9%E3%83%86%E3%82%A3%E3%83%BC%E3%83%96%E3%83%B3%E3%82%B9/dp/4894712059)
- [The Linux Programming Interface](https://www.oreilly.co.jp/books/9784873115856/)

## Web
- [Internet Relay Chat — The UChicago χ-Projects](http://chi.cs.uchicago.edu/chirc/irc.html)

## RFC
- [RFC 1459](https://datatracker.ietf.org/doc/html/rfc1459)
- [RFC 2811](https://datatracker.ietf.org/doc/html/rfc2811)
- [RFC 2812](https://datatracker.ietf.org/doc/html/rfc2812)

## IRC
- [inspircd](https://www.inspircd.org/)

## AI
- RFC translation
- Support for reading inspircd source code
- Class design support
- Discussion support for understanding I/O multiplexing and non-blocking concepts (epoll, poll, select, etc.)
- Test case identification and Python syntax support
- README translation

# Command Reference

## Connection Registration
| Command | Parameters | Description |
|-----|-----|-----|
| `PASS` | \<password\> | Sends the connection password to the server. |
| `NICK` | \<nickname\> | Used to give a user a nickname or change an existing nickname. Nicknames must be unique. |
| `USER` | \<user\> \<mode\> \<unused\> \<realname\> | Registers user information at connection. Combined with NICK, completes the connection registration. The mode parameter is for setting user modes, which are not implemented in this project. |
| `QUIT` | (\<Quit Message\>) | Disconnects from the server. If a message is specified, it is displayed as the quit message. |

## Channel Operations
| Command | Parameters | Description |
|-----|-----|-----|
| `JOIN` | \<channel\> (\<key\>) | Joins the specified channel. If the channel does not exist, it is created. A key is required for channels with a key set. |
| `PART` | \<channel\> (\<Part Message\>) | Leaves the specified channel. If a message is specified, it is displayed as the part message. |
| `MODE` | \<channel\> ((+/-)\<mode\> \<modeparams\>) | Sets the mode of a channel. If only the channel is specified, the current mode of that channel is displayed. The following modes are available:<br> `+i`: Sets the channel to invite-only <br> `+t`: Restricts TOPIC changes to operators only <br> `+k`: Sets a password for the channel <br> `+l`: Sets the maximum number of users in the channel <br> `+n`: Prohibits messages from outside the channel <br> `+o`: Grants operator privileges to the specified user |
| `TOPIC` | \<channel\> (\<topic\>) | Sets the channel topic. If no topic is specified, the current topic is displayed. |
| `NAMES` | \<channel\> | Displays the list of users in the specified channel. |
| `LIST` | (\<channel\>) | Displays a list of channels. If a channel is specified, only that channel's information is shown. |
| `INVITE` | \<nickname\> \<channel\> | Invites the specified user to a channel. Operator privileges are required for invite-only channels (+i). |
| `KICK` | \<channel\> \<nickname\> (\<comment\>) | Forces the specified user to leave the channel. Operator privileges are required. |

## Sending Messages
| Command | Parameters | Description |
|-----|-----|-----|
| `PRIVMSG` | \<msgtarget\> \<text to be sent\> | Sends a message to the specified user or channel. |
| `NOTICE` | \<msgtarget\> \<text to be sent\> | Sends a message to the specified user or channel. Unlike PRIVMSG, it does not generate automatic replies. |

## Service Queries and Commands
| Command | Parameters | Description |
|-----|-----|-----|
| `MOTD` | - | Displays the server's message of the day. |


# Tester
[command tester](https://github.com/kaisuzuk2/42-ft_irc_tester)

## Installation

```bash
git clone https://github.com/kaisuzuk2/42-ft_irc_tester.git
```

## Requirements

- python3

## How to Run
- Start the server in a separate terminal before running.

```bash
python3 tester/tester.py
```
