/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-14 01:37:41 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-14 01:37:41 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>

class Client
{
    private:
        int                 _fd;
        std::string         _hostname;
        std::string         _password;

        std::string         _recvBuf;
        std::string         _sendBuf;
    public:
        Client(int fd, const struct sockaddr_in &addr);
        ~Client();

        int                 _getFd() const;
        const std::string   &_getHostname() const;
        void                _setPassword(const std::string &pass);
        const std::string   &_getpassword() const;

        void                _appendToBuffer(const char *data, int len);
        bool                _getNextLine(std::string &line);
        void                _send(const std::string &msg);
        void                _flushSendBuf();
};

#endif