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
#include "Client.hpp"

class ClientManager 
{
    private:
        std::map<int, Client*>  _clients;
    public:
        ClientManager();
        ~ClientManager();

        void                    addClient(int fd, Client *client);
        void                    removeClient(int fd);
        Client                  *findByFd(int fd) const;
};  

#endif