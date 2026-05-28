/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-23 23:38:54 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-23 23:38:54 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"

Channel::Channel(const std::string &name)
    : _name(name)
    , _topicSetAt(0)
    , _modes(0) // ### TODO: デフォルトのモード追加しよう
    , _limit(0)
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

const std::string &Channel::_getKey() const
{
    return (this->_key);
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

bool Channel::_isEmpty() const
{
    return (this->_members.empty());
}

/*
    ### TODO:
    @#channelで管理者だけに送信できる
*/
void Channel::_broadcast(const std::string &msg, Client *except)
{
    std::map<Client *, bool>::const_iterator it;
    
    it = this->_members.begin();
    for (; it != this->_members.end(); ++it)
    {
        if (it->first != except)
            it->first->_send(msg);
    }
}

void Channel::_sendNames(Client &client, const std::string servername) const
{
    std::string nameList;

    std::map<Client *, bool>::const_iterator it = this->_members.begin();
    for (; it != this->_members.end(); ++it)
    {
        if (it->second)
            nameList += "@";
        nameList += it->first->_getNick() + " ";
    }
    
    // ### TODO:  = はチャンネルの種類によるもの
    client._writeNumeric(RPL_NAMREPLY, + servername, " = " + this->_name + " :" + nameList);
}


bool Channel::_isModeSet(unsigned int mode) const
{
    return ((this->_modes & mode) != 0);
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


