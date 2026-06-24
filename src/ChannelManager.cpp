/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 00:35:25 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/06/24 09:42:38 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>

#include "ChannelManager.hpp"
#include "Channel.hpp"
#include "ft_ircd.hpp"

ChannelManager::ChannelManager() {}

ChannelManager::~ChannelManager() 
{
    std::map<std::string, Channel *>::iterator it = this->_channels.begin();

    for (; it != this->_channels.end(); ++it)
        delete it->second;
    this->_channels.clear();
}

Channel *ChannelManager::_find(const std::string &name) const
{
    std::string lowerCh;

    lowerCh = name;
    std::transform(lowerCh.begin(), lowerCh.end(), lowerCh.begin(), FtIRCd::_rfcTolower);
    std::map<std::string, Channel *>::const_iterator it = this->_channels.find(lowerCh);
    if (it == this->_channels.end())
        return (NULL);
    return (it->second);
}

// チャンネル名は大文字小文字を区別しないので、キーはすべて小文字で統一する
Channel *ChannelManager::_create(const std::string &name)
{  
    Channel *ch;
    std::string lowerCh;

    ch = new Channel(name);
    lowerCh = name;
    std::transform(lowerCh.begin(), lowerCh.end(), lowerCh.begin(), FtIRCd::_rfcTolower);
    this->_channels[lowerCh] = ch;
    return (ch);
}

void ChannelManager::_remove(const std::string &name)
{
    std::string lowerName = name;
    std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), FtIRCd::_rfcTolower);
    std::map<std::string, Channel *>::iterator it = this->_channels.find(lowerName);
    if (it == this->_channels.end())
        return ;

    Channel *ch = it->second;
    const std::set<Client *> &inviteList = ch->_getInviteList();
    for (std::set<Client *>::const_iterator cit = inviteList.begin(); cit != inviteList.end(); ++cit)
    {
        (*cit)->_removeInvitedChannel(ch);
    }

    delete ch;
    this->_channels.erase(it);
}

bool ChannelManager::_isPrefix(unsigned char prefix)
{
    return (prefix == '#');
}

bool ChannelManager::_isStatusPrefix(unsigned char prefix)
{
    return (prefix == '@');
}

const std::map<std::string, Channel *> &ChannelManager::_getChannels() const
{
    return (this->_channels);
}
