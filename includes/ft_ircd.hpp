/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ircd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-15 00:10:38 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-15 00:10:38 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRCD_HPP
# define FT_IRCD_HPP

#include <string>

#include "SocketEngine.hpp"
#include "ClientManager.hpp"
#include "CommandParser.hpp"
#include "ChannelManager.hpp"
#include "Numeric.hpp"

class FtIRCd 
{
    private:
        int                 _port;
        std::string         _password;
        int                 _serverFd;
        std::string         _servername;
        
        SocketEngine        _socketEngine;
        ClientManager       _clients;
        ChannelManager      _channels;
        CommandParser       _parser;

    public:
        FtIRCd(int argc, char **argv);
        ~FtIRCd();

        void                    _run();
        void                    _checkRegister(Client &client) const;

    private:
        void                    _parseConfig(int argc, char **argv);
        int                     _parsePort(const char *str) const;
        std::string             _parsePassword(const std::string &str) const;

        void                    _acceptClient();
        void                    _handleClient(int fd);
        void                    _disconnectClient(int fd);

        static const int        kPortMin = 1024;
        static const int        kPortMax = 65535; // ### TODO: これ正しいかチェックする
        static const int        kArgNum = 3;
        static const int        kArgIdxPort = 1;
        static const int        kArgIdxPassword = 2;


    public: // ### TODO: const版いるかどうか考えよう
        const std::string       &_getServername() const;
        ClientManager           &_getClients();
        const ClientManager     &_getClients() const;
        ChannelManager          &_getChannels();
        const ChannelManager    &_getCannels() const;

        static const size_t     kMaxNickLen = 9;
        static const size_t     kMaxUserLen = 9;
        static const size_t     kMaxChanLen = 50; // RFC2811 2.1
};

#endif