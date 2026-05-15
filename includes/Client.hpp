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

        std::string         _recvBuf;
        std::string         _sendBuf;
    public:
        Client(int fd, const struct sockaddr_in &addr);
        ~Client();

        int                 getFd() const;
        const std::string & getHostname() const;

        void                appendToBuffer(const char *data, int len);
        bool                getNextLine(std::string &line);
        void                send(const std::string &msg);
        void                flushSendBuf();
};

#endif