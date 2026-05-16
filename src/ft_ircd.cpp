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

#include "ft_ircd.hpp"
#include "SocketEngine.hpp"
#include "Client.hpp"
#include "CommandParser.hpp"

const std::string &FtIRCd::_getServername() const 
{
    return (this->_servername);
}

std::string FtIRCd::_parsePassword(const std::string &str) const 
{
    if (str.empty())
        throw std::invalid_argument("Error: password cannot be empty");
    return (str);
}

int FtIRCd::_parsePort(const char *str) const
{
    char *endptr;
    long res;

    errno = 0;
    endptr = NULL;
    res = std::strtol(str, &endptr, 10);
    if (str == endptr)
        throw std::invalid_argument("Error: Port is not a number: " + std::string(str));
    else if (errno == ERANGE)
        throw std::overflow_error("Error: Port number overflow: " + std::string(str));
    if (*endptr != '\0')
        throw std::invalid_argument("Error: Port contains invalid characters: " + std::string(str));
    if (res < kPortMin || res > kPortMax) // ### TODO: kPortMaxとkPortMinを使うべき
        throw std::out_of_range("Error: Port out of range (1024 - 65535): " + std::string(str));
    return (static_cast<int>(res));
}

void FtIRCd::_parseConfig(int argc, char **argv)
{
    // ### TODO: 定数マクロ化する
    if (argc < kArgNum)
        throw std::invalid_argument("Usage: ./ircserv <port> <password>");
    this->_port = this->_parsePort(argv[kArgIdxPort]);
    this->_password = this->_parsePassword(argv[kArgIdxPassword]);
}

void FtIRCd::_disconnectClient(int fd) 
{
    std::cout << "client disconnected: fd = " << fd << std::endl;
    this->_socketEngine._delFd(fd);
    this->_clients._removeClient(fd);
}

void FtIRCd::_handleClient(int fd) 
{
    Client *client;
    char buf[512];
    int n;
    std::string line;

    client = this->_clients._findByFd(fd);
    n = recv(fd, buf, sizeof(buf) - 1, 0);
    if (n <= 0)
    {
        this->_disconnectClient(fd);
        return ;
    }

    client->_appendToBuffer(buf, n);
    while (client->_getNextLine(line))
        this->_parser._process(*this, *client, line);
    
    client->_flushSendBuf();
}

void FtIRCd::_acceptClient()
{
    struct sockaddr_in client_addr;
    socklen_t client_len;
    int client_fd;

    client_len = sizeof(client_addr);
    // ### TODO: accept4使っていいかな
    client_fd = accept4(this->_serverFd, (struct sockaddr *)&client_addr, &client_len, SOCK_NONBLOCK);
    if (client_fd < 0)
    {
        std::cerr << "accept4() failed: " << std::strerror(errno) << std::endl;
        return ;
    }
    this->_socketEngine._addFd(client_fd, EPOLLIN);
    this->_clients._addClient(client_fd, new Client(client_fd, client_addr));

    std::cout << "client connected: " << this->_clients._findByFd(client_fd)->_getHostname() << std::endl;

    this->_clients._findByFd(client_fd)->_send("hello");
    this->_clients._findByFd(client_fd)->_flushSendBuf();
}

void FtIRCd::_run() 
{
    int fd;

    while (1)
    {
        // ### TODO: -1でいいか再考すること
        std::vector<int> readyFds = this->_socketEngine._dispatch(-1);
        for (size_t i = 0; i < readyFds.size(); ++i)
        {
            fd = readyFds[i];
            if (fd == this->_serverFd)
                this->_acceptClient();
            else
                this->_handleClient(fd);        
        }
    }
}

FtIRCd::~FtIRCd() 
{
    if (this->_serverFd >= 0)
        close(this->_serverFd);
}

FtIRCd::FtIRCd(int argc, char **argv)
    : _servername("ft_irc.local")
{
    this->_parseConfig(argc, argv);

    this->_serverFd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(this->_serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(this->_port);
    
    bind(this->_serverFd, (struct sockaddr *)&addr, sizeof(addr));

    listen(this->_serverFd, 10);
    std::cout << "Listening on port " << this->_port << std::endl;

    this->_socketEngine._addFd(this->_serverFd, EPOLLIN);
}

int main(int argc, char *argv[])
{
    try 
    {
        FtIRCd ServerInstance(argc, argv);
        ServerInstance._run();
    } 
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return (EXIT_SUCCESS);
}