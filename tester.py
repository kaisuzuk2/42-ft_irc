import socket

nick = "alice"
passwd = "pass"

GREEN = "\033[32m"
RED   = "\033[31m"
RESET = "\033[0m"  

##############################################################################
def connect():
    s = socket.create_connection(("127.0.0.1", 6667))
    return (s)

def login(s, nick, passwd):
    s.sendall(f"PASS {passwd}\r\nNICK {nick}\r\nUSER {nick} 0 * :{nick}\r\n".encode())
    return (s.recv(4096).decode())

def ok(name, response, expected):
    if expected in response:
        print(f"{name.ljust(45)}: {GREEN}PASS{RESET}")
    else:
        print(f"{name.ljust(45)}: {RED}FAIL{RESET}")
        print(f"    expected: {expected}")
        print(f"    yours: {response[:100]}")

def ok_all(name, responce, expected_list):
    results = []
    failed = []
    for expected in expected_list:
        if expected in responce:
            results.append(f"{GREEN}PASS{RESET}")
        else:
            results.append(f"{RED}FAIL{RESET}")
            failed.append(expected)
    print(f"{name.ljust(45)}: {' '.join(results)}")
    for f in failed:
        print(f"    expected: {f}")

class Client:
    def __init__(self, nick, passwd):
        self.s = connect()
        self.r = login(self.s, nick, passwd)

    def send(self, cmd):
        self.s.sendall((cmd + "\r\n").encode())

    def recv(self):
        self.r = self.s.recv(4096).decode()
        return (self.r)
    
    def close(self):
        self.s.close()

###########################################################################
# testcode

## connection test
def connection():
    alice = Client(nick, passwd)
    ok("connection -> 001", alice.r, "001")
    alice.close()

def wrong_passwd():
    alice = Client(nick ,"wrongpass")
    ok("wrong_passwd -> 464", alice.r, "464")
    alice.close()

def invalid_toolong_nick():
    alice = Client("toolongnick", passwd)
    ok("invalid_toolong_nick -> 432", alice.r, "432")
    alice.close()

def invalid_special_nick():
    alice = Client("hello!", passwd)
    ok("invalid_special_nick -> 432", alice.r, "432")
    alice.close()

def special_nick():
    alice = Client("[]\\`_^{|", passwd)
    ok("special_nick -> 001", alice.r, "001")
    alice.close()

def nick_starts_with_number():
    alice = Client("1abc", passwd)
    ok("nick starts with number -> 432", alice.r, "432")
    alice.close()

def nick_number_in_second():
    alice = Client("a1bc", passwd)
    ok("nick number in second -> 001", alice.r, "001")
    alice.close()

## join test
def join_no_param():
    alice = Client(nick, passwd)
    alice.send("JOIN")
    r = alice.recv()
    ok("join_no_param", r, "461")
    alice.close()

def join_channel():
    alice = Client(nick, passwd)
    alice.send("JOIN #test")
    r = alice.recv()
    ok_all("join_channel", r, ["JOIN", "353", "366"])
    alice.close()

def join_invalid_channel():
    alice = Client(nick, passwd)
    alice.send("JOIN badchannel")
    r = alice.recv()
    ok("join_invalid_channel", r, "476")
    alice.close()

def join_invalid_channel_space():
    alice = Client(nick, passwd)
    alice.send("JOIN :#hello world")
    r = alice.recv()
    ok("join_invalid_channel_space", r, "476")
    alice.close()

def join_multiple_channel():
    alice = Client(nick, passwd)
    alice.send("JOIN #test1,#test2,#test3")
    r = alice.recv()
    ok_all("join_multiple_channel", r, ["JOIN :#test1", "JOIN :#test2", "JOIN :#test3"])
    alice.close()

def join_multiple_channel_one_invalid():
    alice = Client(nick, passwd)
    alice.send("JOIN #test1,badchannel,#test3")
    r = alice.recv()
    ok_all("join_multiple_channel_one_invalid", r, ["JOIN :#test1", "JOIN :#test3", "476"])
    alice.close()

def join_over_limit():
    alice = Client(nick, passwd)
    alice.send("JOIN #1,#2,#3,#4,#5,#6,#7,#8,#9,#10,#11")
    r = alice.recv()
    ok("join_over_limit", r, "405")
    alice.close()

## privmsg test
def privmsg_no_target():
    alice = Client(nick, passwd)
    alice.send("PRIVMSG")
    r = alice.recv()
    ok("privmsg_no_target", r, "461")
    alice.close()

def privmsg_no_message():
    alice = Client(nick, passwd)
    alice.send(f"PRIVMSG {nick}")
    r = alice.recv()
    ok("privmsg_no_message", r, "461")
    alice.close()

def privmsg_empty_message():
    alice = Client(nick, passwd)
    alice.send(f"PRIVMSG {nick} :")
    r = alice.recv()
    ok("privmsg_empty_message", r, "412")
    alice.close()

def privmsg_to_channel():
    channel = "#test"
    alice = Client(nick, passwd)
    bob = Client("bob", passwd)
    alice.send(f"JOIN {channel}")
    alice.recv()
    bob.send(f"JOIN {channel}")
    bob.recv()
    alice.send(f"PRIVMSG {channel} :Hello bob!")
    r = bob.recv()
    ok("privmsg_to_channel", r, "Hello bob!")
    alice.close()
    bob.close()

def privmsg_to_nobody():
    alice = Client(nick, passwd)
    alice.send("PRIVMSG nobody :hello")
    r = alice.recv()
    ok("privmsg_to_nobody", r, "401")
    alice.close()

def privmsg_to_invalid_channel():
    alice = Client(nick, passwd)
    alice.send("PRIVMSG #badchannel :hello")
    r = alice.recv()
    ok("privmsg_to_invalid_channel", r, "403")
    alice.close()

## connection test
print("========== connection test ==========")
connection()
wrong_passwd()
invalid_toolong_nick()
invalid_special_nick()
special_nick()
nick_starts_with_number()
nick_number_in_second()

## join test
# TODO: join 0
print("========== join test ==========")
join_channel()
join_invalid_channel()
join_invalid_channel_space()
join_multiple_channel()
join_multiple_channel_one_invalid()
join_over_limit()

## privmsg test
print("========== privmsg test ==========")
privmsg_no_target()
privmsg_no_message()
privmsg_empty_message()
privmsg_to_channel()
privmsg_to_nobody()
