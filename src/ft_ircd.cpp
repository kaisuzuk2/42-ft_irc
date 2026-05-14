/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ircd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-14 00:22:58 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-14 00:22:58 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <map>

#include <cerrno>

#include <sys/epoll.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "SocketEngine.hpp"
#include "Client.hpp"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;
        return (EXIT_FAILURE);
    }

    int port = std::atoi(argv[1]);

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    
    bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));

    listen(server_fd, 10);
    std::cout << "Listening on port " << port << std::endl;

    SocketEngine socketEngine;
    socketEngine.addFd(server_fd, EPOLLIN);

    std::map<int, Client *> clients;

    char buf[512];

    while (true)
    {
        std::vector<int> readyFds = socketEngine.dispatch(-1);
        
        for (size_t i = 0; i < readyFds.size(); ++i)
        {
            int fd = readyFds[i];

            if (fd == server_fd)
            {
                struct sockaddr_in client_addr;
                socklen_t client_len = sizeof(client_addr);
                // ### TODO: accept4使っていいかな
                int client_fd = accept4(server_fd, (struct sockaddr *)&client_addr, &client_len, SOCK_NONBLOCK);
                if (client_fd < 0)
                {
                    std::cerr << "accept4() failed: " << std::strerror(errno) << std::endl;
                    continue ;
                }
                socketEngine.addFd(client_fd, EPOLLIN);

                clients[client_fd] = new Client(client_fd, client_addr);

                std::cout << "client connected: " << clients[client_fd]->getHostname() << std::endl;

                clients[client_fd]->send("hello");
                clients[client_fd]->flushSendBuf();
            }
            else
            {
                int n = recv(fd, buf, sizeof(buf) - 1, 0);
                if (n <= 0)
                {
                    std::cout << "client disconnected: fd = " << fd << std::endl;
                    socketEngine.delFd(fd);
                    delete clients[fd];
                    clients.erase(fd);
                    close(fd);
                }
                else
                {
                    clients[fd]->appendToBuffer(buf, n);
                    std::string line;
                    while (clients[fd]->getNextLine(line))
                        std::cout << "fd = " << fd << " says: " << line << std::endl;
                }
            }
        }
    }
    close(server_fd);
    return (EXIT_SUCCESS);
}