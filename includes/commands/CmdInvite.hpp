/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdInvite.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 22:20:57 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/06/24 09:41:08 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDINVITE_HPP
# define CMDINVITE_HPP

#include "ACommand.hpp"
#include "Channel.hpp"

class CmdInvite: public ACommand
{
    public:
        CmdInvite();
        ~CmdInvite();

        void    _execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params);
    
    private:
        bool    _preInviteCheck(FtIRCd &serverInstance, Client &client, Channel *ch) const;
};


#endif
