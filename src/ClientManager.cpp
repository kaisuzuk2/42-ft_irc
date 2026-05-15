/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-14 23:30:19 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-14 23:30:19 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientManager.hpp"

ClientManager::ClientManager() {}

ClientManager::~ClientManager() 
{
    for (std::map<int, Client *>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++)
        delete(it->second);
    this->_clients.clear();
}

void ClientManager::_addClient(int fd, Client *client)
{
    this->_clients[fd] = client;
}

void ClientManager::_removeClient(int fd)
{
    std::map<int, Client *>::iterator it = this->_clients.find(fd);
    if (it == this->_clients.end())
        return ;
    delete it->second;
    this->_clients.erase(it);
}

Client *ClientManager::_findByFd(int fd) const 
{
    std::map<int, Client *>::const_iterator it = this->_clients.find(fd);
    if (it == this->_clients.end())
        return (NULL);
    return (it->second);
}

