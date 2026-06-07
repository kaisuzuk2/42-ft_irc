/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-24 00:13:56 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-24 00:13:56 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNELMANAGER_HPP
# define CHANNELMANAGER_HPP

#include <string>
#include <map>

class Channel;

class ChannelManager 
{
    private:
        std::map<std::string, Channel *>    _channels; // キーは小文字

    public:
        ChannelManager();
        ~ChannelManager();

        Channel                             *_find(const std::string &name) const;
        Channel                             *_create(const std::string &name);
        void                                _remove(const std::string &name); // ### TODO: channel受け取ってもいいかもね
       
        static bool                         _isPrefix(unsigned char prefix);
        static bool                         _isStatusPrefix(unsigned char prefix);
};

#endif