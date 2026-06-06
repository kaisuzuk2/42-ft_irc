/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelManager.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-24 00:35:25 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-24 00:35:25 by kaisuzuk         ###   ########.fr       */
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
    std::map<std::string, Channel *>::iterator it = this->_channels.find(name);
    if (it == this->_channels.end())
        return ;
    delete it->second;
    this->_channels.erase(it);
}

bool ChannelManager::_isPrefix(unsigned char prefix)
{
    return (prefix == '#');
}