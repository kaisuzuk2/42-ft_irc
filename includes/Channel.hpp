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
#include <ctime>

class Client;

class Channel
{
    private:
        std::string                 _name;
        std::string                 _topic;
        std::string                 _topicSetBy;
        time_t                      _topicSetAt;
        std::map<Client *, bool>    _members;
        unsigned int                _modes;
        std::string                 _key;
        unsigned int                _limit;

    public:
        Channel(const std::string &name);
        ~Channel();

        void                        _addMember(Client *client, bool isOper = false);
        void                        _removeMember(Client *client);
        bool                        _hasMember(Client *client) const;
        bool                        _isOper(Client *client) const;
        bool                        _isEmpty() const;
        
        const std::string           &_getName() const;
        const std::string           &_getTopic() const;
        const std::string           &_getKey() const;
};

#endif