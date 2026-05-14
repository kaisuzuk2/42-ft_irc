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

    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);

    std::cout << "client connected!" << std::endl;

    const char *msg = "hello\r\n";
    send(client_fd, msg, strlen(msg), 0);

    close(client_fd);
    close(server_fd);
    return (EXIT_SUCCESS);
}