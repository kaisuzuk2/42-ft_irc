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

#include "ChannelManager.hpp"

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
    std::map<std::string, Channel *>::const_iterator it = this->_channels.find(name);
    if (it == this->_channels.end())
        return (NULL);
    return (it->second);
}

Channel *ChannelManager::_create(const std::string &name)
{  
    Channel *ch;

    ch = new Channel(name); 
    this->_channels[name] = ch;
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