/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-14 23:26:34 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-14 23:26:34 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTMANAGER_HPP
# define CLIENTMANAGER_HPP

#include <map>
#include <algorithm>

#include "Client.hpp"

class ClientManager 
{
    private:
        std::map<int, Client*>  _clients;
        static char             _toLower(char c);
    public:
        ClientManager();
        ~ClientManager();

        void                    _addClient(int fd, Client *client);
        void                    _removeClient(int fd);

        Client                  *_findByFd(int fd) const;
        Client                  *_findByNick(const std::string &nick) const;
};  

#endif