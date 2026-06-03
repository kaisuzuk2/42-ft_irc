/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-23 23:23:24 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-23 23:23:24 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <string>
#include <map>
#include <set>
#include <ctime>

#include "Numeric.hpp"

class Client;

enum ChannelMode
{
    MODE_INVITE_ONLY    = 0x01, // +i
    MODE_TOPIC_OP       = 0x02, // +t
    MODE_KEY            = 0x04, // +k
    MODE_LIMIT          = 0x08, // +l
    MODE_NO_EXTERNAL    = 0x10, // +n
};

class Channel
{
    private:
        std::string                         _name;
        std::string                         _topic;
        std::string                         _topicSetBy;
        time_t                              _topicSetAt;
        std::map<Client *, bool>            _members;
        unsigned int                        _modes;
        std::string                         _key;
        unsigned int                        _limit;
        std::set<Client *>                  _inviteList;
        time_t                              _createdAt;

    public:
        Channel(const std::string &name);
        ~Channel();

        void                                _addMember(Client *client, bool isOper = false);
        void                                _removeMember(Client *client);
        bool                                _hasMember(Client *client) const;

        bool                                _isOper(Client *client) const;
        void                                _setOper(Client *client, bool isOper);

        bool                                _isEmpty() const;
    
        bool                                _isModeSet(unsigned int mode) const;
        void                                _setMode(unsigned int mode);
        void                                _unsetMode(unsigned int mode);

        bool                                _isInvited(Client *client) const;
        void                                _addInvite(Client *client);
        void                                _removeInvite(Client *client);

        void                                _broadcast(const std::string &msg, Client *except);
        
        void                                _sendNames(Client &client, const std::string &servername) const;

        void                                _showTopic(Client &client, const std::string &servername) const;
        void                                _displayModes(Client &client, const std::string &servername) const;

        const std::string                   &_getName() const;
        const std::string                   &_getTopic() const;
        void                                _setTopic(const std::string &topic, const std::string &setBy, time_t setAt);
        const std::string                   &_getKey() const;
        void                                _setKey(const std::string &key);

        void                                _setLimit(unsigned int limit);
        unsigned int                        _getLimit() const;

        size_t                              _getMemberSize() const;
        const &std::map<Client *, bool>     _getMembers() const;
};

#endif