/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 23:38:54 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/06/24 09:42:29 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>

#include "Channel.hpp"
#include "Client.hpp"

Channel::Channel(const std::string &name)
    : _name(name)
    , _topicSetAt(0)
    , _modes(MODE_NO_EXTERNAL | MODE_TOPIC_OP) // [Note] inspircdよりデフォルトのチャンネルモード設定
    , _limit(0)
    , _createdAt(std::time(NULL)) 
{}

Channel::~Channel() {}

const std::string &Channel::_getName() const 
{
    return (this->_name);
}

const std::string &Channel::_getTopic() const
{
    return (this->_topic);
}

void Channel::_setTopic(const std::string &topic, const std::string &setBy, time_t setAt)
{
    this->_topic = topic;
    this->_topicSetBy = setBy;
    this->_topicSetAt = setAt;
    
    this->_broadcast(":" + setBy + " TOPIC " + this->_name + " :" + topic, NULL, false);
}

const std::string &Channel::_getKey() const
{
    return (this->_key);
}

void Channel::_setKey(const std::string &key)
{
    this->_key = key;
}

void Channel::_setLimit(unsigned int limit)
{
    this->_limit = limit;
}

unsigned int Channel::_getLimit() const
{
    return (this->_limit);
}

void Channel::_addMember(Client *client, bool isOper)
{
    this->_members[client] = isOper;
}

void Channel::_removeMember(Client *client)
{
    this->_members.erase(client);
}

bool Channel::_hasMember(Client *client) const
{
    return (this->_members.find(client) != this->_members.end());
}

bool Channel::_isOper(Client *client) const
{
    std::map<Client *, bool>::const_iterator it = this->_members.find(client);
    if (it == this->_members.end())
        return (false);
    return (it->second);
}

void Channel::_setOper(Client *client, bool isOper)
{
    this->_members[client] = isOper;
}

bool Channel::_isEmpty() const
{
    return (this->_members.empty());
}

void Channel::_broadcast(const std::string &msg, Client *except, bool operOnly)
{
    std::map<Client *, bool>::const_iterator it;
    
    it = this->_members.begin();
    for (; it != this->_members.end(); ++it)
    {
        if (it->first == except)
            continue ;
        if (operOnly && !it->second)
            continue ;
        it->first->_send(msg);
    }
}

void Channel::_sendNames(Client &client, const std::string &servername) const
{
    std::string nameList;

    std::map<Client *, bool>::const_iterator it = this->_members.begin();
    for (; it != this->_members.end(); ++it)
    {
        if (it->second)
            nameList += "@";
        nameList += it->first->_getNick() + " ";
    }
    
    client._writeNumeric(RPL_NAMREPLY, servername, "= " + this->_name + " :" + nameList);
}

void Channel::_showTopic(Client &client, const std::string &servername) const
{
    std::ostringstream oss;

    client._writeNumeric(RPL_TOPIC, servername, this->_name + " :" + this->_topic);
    oss << this->_topicSetAt;
    client._writeNumeric(RPL_TOPICTIME, servername, this->_name + " " + _topicSetBy + " :" + oss.str());
}

// ### core_mode.cpp
void Channel::_displayModes(Client &client, const std::string &servername) const
{
    std::ostringstream modes;
    std::ostringstream params;

    modes << "+";

    if (this->_isModeSet(MODE_INVITE_ONLY)) modes << "i";
    if (this->_isModeSet(MODE_NO_EXTERNAL)) modes << "n";
    if (this->_isModeSet(MODE_TOPIC_OP)) modes << "t";
    if (this->_isModeSet(MODE_LIMIT))
    {
        modes << "l";
        params << " " << this->_limit;
    }
    if (this->_isModeSet(MODE_KEY))
    {
        modes << "k";
        params << " :";
        if (this->_hasMember(&client))
            params << this->_key;
        else
            params << "<key>";
    }

    client._writeNumeric(RPL_CHANNELMODEIS, servername, this->_name + " " + modes.str()  + params.str());
    std::ostringstream oss;
    oss << this->_createdAt;
    client._writeNumeric(RPL_CHANNELCREATED, servername, this->_name + " :" + oss.str());
    
}

bool Channel::_isModeSet(unsigned int mode) const
{
    return ((this->_modes & mode) != 0);
}

void Channel::_setMode(unsigned int mode)
{
    this->_modes |= mode;
}

void Channel::_unsetMode(unsigned int mode)
{
    this->_modes &= ~mode;
}

bool Channel::_isInvited(Client *client) const
{
    return (this->_inviteList.find(client) != this->_inviteList.end());
}

void Channel::_addInvite(Client *client)
{
    this->_inviteList.insert(client);
}

void Channel::_removeInvite(Client *client)
{
    this->_inviteList.erase(client);
}

const std::set<Client *> &Channel::_getInviteList() const
{
    return (this->_inviteList);
}

size_t Channel::_getMemberSize() const
{
    return (this->_members.size());
}

const std::map<Client *, bool> &Channel::_getMembers() const
{
    return (this->_members);
}
