/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-14 02:51:13 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-14 02:51:13 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <stdexcept>
#include <cerrno>
#include <cstring>
#include <unistd.h>

Client::Client(int fd, const struct sockaddr_in &addr)
    : _fd(fd)
{
    char ip[INET_ADDRSTRLEN];
    if ( inet_ntop(AF_INET, &addr.sin_addr, ip, sizeof(ip)) == NULL)
        throw std::runtime_error("ient_ntop() failed: " + std::string(std::strerror(errno)));
    this->_hostname = std::string(ip);
}

Client::~Client()
{
    if (this->_fd >= 0)
        close(this->_fd);
}

int Client::getFd() const 
{
    return (this->_fd);
}

const std::string &Client::getHostname() const 
{
    return (this->_hostname);
}