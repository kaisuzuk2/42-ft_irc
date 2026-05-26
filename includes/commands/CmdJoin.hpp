/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdJoin.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-24 01:48:35 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-24 01:48:35 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDJOIN_HPP
# define CMDJOIN_HPP

#include "ft_ircd.hpp"
#include "ACommand.hpp"
#include "Channel.hpp"

class CmdJoin: public ACommand
{
    public:
        CmdJoin();
        ~CmdJoin();

        void    _execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params);
    
    private:
        void    _joinChannel(FtIRCd &serverInstance, Client &client, const std::string &cname, const std::string &key);
        bool    _preJoinCheck(FtIRCd &serverInstance, Client &client, Channel *ch, const std::string &cname, const std::string &key);

        bool    _isValidChannelName(const std::string &name) const;
        bool    _isPrefix(unsigned char prefix) const;
};

#endif