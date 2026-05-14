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

#include <sys/epoll.h>
#include <netinet/in.h>
#include <sys/socket.h>

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

    int epfd = epoll_create1(0);

    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = server_fd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, server_fd, &ev);

    struct epoll_event events[64];

    while (true)
    {
        int nfds = epoll_wait(epfd, events, 64, -1);
        
        for (int i = 0; i < nfds; ++i)
        {
            int fd = events[i].data.fd;

            if (fd == server_fd)
            {
                struct sockaddr_in client_addr;
                socklen_t client_len = sizeof(client_addr);
                int client_fd = accept4(server_fd, (struct sockaddr *)&client_addr, &client_len, SOCK_NONBLOCK);

                ev.events = EPOLLIN;
                ev.data.fd = client_fd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, client_fd, &ev);

                std::cout << "client connected: fd = " << client_fd << std::endl;

                const char *msg = "hello\r\n";
                send(client_fd, msg, strlen(msg), 0);
            }
            else
            {
                char buf[512];
                int n = recv(fd, buf, sizeof(buf) - 1, 0);
                if (n <= 0)
                {
                    std::cout << "client disconnected: fd = " << fd << std::endl;
                    epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
                    close(fd);
                }
                else
                {
                    buf[n] = '\0';
                    std::cout << "fd = " << fd << "says: " << buf << std::endl;
                }
            }
        }
    }
    close(server_fd);
    close(epfd);
    return (EXIT_SUCCESS);
}