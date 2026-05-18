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

#include <sys/types.h>
#include <sys/socket.h> 

#include "ClientManager.hpp"

Client::Client(int fd, const struct sockaddr_in &addr)
    : _fd(fd)
    , _nick("*")
    , _username("")
    , _isregistered(false)
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

bool Client::_changeNick(const std::string &newnick, const ClientManager &clients, const std::string &servername)
{
    Client *const InUse = clients._findByNick(newnick);

    if (InUse == this)
    {
        if (newnick == this->_nick)
            return (true);
    }
    else if (InUse)
    {
        this->_send(":" + servername + " 433 " + this->_getNick() + " " + newnick + " :Nickname is already in use");
        return (false);
    }
    this->_nick = newnick;
    return (true);
    
}

int Client::_getFd() const 
{
    return (this->_fd);
}

const std::string &Client::_getHostname() const 
{
    return (this->_hostname);
}

void Client::_setPassword(const std::string &pass)
{
    this->_password = pass;
}

const std::string &Client::_getPassword() const
{
    return (this->_password);
}

void Client::_setNick(const std::string &nick)
{
    this->_nick = nick;
}

const std::string &Client::_getNick() const
{
    return (this->_nick);
}

bool Client::_isRegistered() const
{
    return (this->_isregistered);
}

const std::string &Client::_getUsername() const
{
    return (this->_username);
}

void Client::_setUsername(const std::string &username) const
{
    this->_username = username;
}

void Client::_appendToBuffer(const char *data, int len)
{
    this->_recvBuf.append(data, len);
}

bool Client::_getNextLine(std::string &line)
{
    size_t pos;

    pos = this->_recvBuf.find('\n');
    if (pos == std::string::npos)
        return (false);

    line = this->_recvBuf.substr(0, pos);
    this->_recvBuf.erase(0, pos + 1);

    if (!line.empty() && line[line.size() -1] == '\r')
        line.erase(line.size() -1);

    return (true);
}

void Client::_send(const std::string &msg)
{
    this->_sendBuf += msg + "\r\n";
}

void Client::_flushSendBuf()
{
    ssize_t sent;

    if (this->_sendBuf.empty())
        return ;
    // sigpipeを無視する　signal(SIGPIPE, SIG_IGN)するなら不要
    sent = ::send(this->_fd, this->_sendBuf.c_str(), this->_sendBuf.size(), MSG_NOSIGNAL);
    if (sent <= 0) // ### TODO: エラー処理
        return ;
    this->_sendBuf.erase(0, sent);
}