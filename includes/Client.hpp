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
#include <set>

class ClientManager;
class Channel;

class Client
{
    private:
        int                         _fd;
        std::string                 _nick;
        std::string                 _username;
        std::string                 _realname;
        std::string                 _hostname;
        std::string                 _password;
        bool                        _isregistered;

        std::string                 _recvBuf;
        std::string                 _sendBuf;

        std::set<Channel *>         _channels;

        std::set<Channel *>         _invitedChannels;

    public:
        Client(int fd, const struct sockaddr_in &addr);
        ~Client();

        void                        _appendToBuffer(const char *data, int len);
        bool                        _getNextLine(std::string &line);
        void                        _send(const std::string &msg);
        void                        _flushSendBuf();
        void                        _writeNumeric(const int num, const std::string &servername, const std::string &msg);

        bool                        _changeNick(const std::string &newnick, const ClientManager &clients, const std::string &servername);
        void                        _setFullyRegistered();

        void                        _joinChannel(Channel *ch);
        void                        _leaveChannel(Channel *ch);
        size_t                      _getChannelSize() const;
        const std::set<Channel *>   &_getChannels() const;

        void                        _addInvitedChannel(Channel *ch);
        void                        _removeInvitedChannel(Channel *ch);
        bool                        _isInvitedTo(Channel *ch) const;
        const std::set<Channel *>   &_getInvitedChannels() const;

        int                         _getFd() const;
        const std::string           &_getHostname() const;    
        void                        _setPassword(const std::string &pass);
        const std::string           &_getPassword() const;
        void                        _setNick(const std::string &nick);
        const std::string           &_getNick() const;
        bool                        _isRegistered() const;
        const std::string           &_getUsername() const;
        void                        _setUsername(const std::string &username);
        const std::string           &_getRealname() const;
        void                        _setRealname(const std::string &realname);

        const std::string           _getPrefix() const;
};

#endif