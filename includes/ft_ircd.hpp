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

#include "NumericReply.hpp"
#include "NumericHelper.hpp"

class FtIRCd 
{
    private:
        int                         _port;
        std::string                 _password;
        int                         _serverFd;
        std::string                 _servername;
        time_t                      _startupTime;

        SocketEngine                _socketEngine;
        ClientManager               _clients;
        ChannelManager              _channels;
        CommandParser               _parser;


    public:
        FtIRCd(int argc, char **argv);
        ~FtIRCd();

        void                        _run();
        void                        _checkRegister(Client &client);

        void                        _quitUser(Client &client, const std::string &reason);
        void                        _disconnectClient(int fd);


    private:
        void                        _parseConfig(int argc, char **argv);
        int                         _parsePort(const char *str) const;
        std::string                 _parsePassword(const std::string &str) const;

        void                        _acceptClient();
        void                        _handleClient(int fd);

        void                        _onUserConnect(Client &client);

        static const int            kPortMin = 1024;
        static const int            kPortMax = 65535;
        static const int            kArgNum = 3;
        static const int            kArgIdxPort = 1;
        static const int            kArgIdxPassword = 2;


    public: 
        const std::string           &_getServername() const;
        ClientManager               &_getClients();
        const ClientManager         &_getClients() const;
        ChannelManager              &_getChannels();
        const ChannelManager        &_getChannels() const;
        CommandParser               &_getParser();
        const CommandParser         &_getParser() const;

        static const size_t         kMaxNickLen = 9; // RFC 2812 2.3.1
        static const size_t         kMaxUserLen = 9;
        static const size_t         kMaxChanLen = 50; // RFC2811 2.1
        static const size_t         kMaxChannels = 10; // RFC1459 1.3
        static const char           *kMotdPath;
        static const std::string    kVersion;
        static const size_t         kMaxMsgLen = 510; // RFC 2812 2.3
        static const size_t         kMaxTopicLen = 330; // inspircd MaxTopic

        static char                 _rfcTolower(char c);
};

#endif