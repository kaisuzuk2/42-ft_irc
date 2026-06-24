/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdKick.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 01:32:49 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/06/24 09:41:20 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDKICK_HPP
# define CMDKICK_HPP

#include "commands/ACommand.hpp"

class CmdKick: public ACommand
{
    public:
        CmdKick();
        ~CmdKick();

        void    _execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params);
    
    private:
        void    _kickUser(FtIRCd &serverInstance, Client &client, const std::string &cname, const std::string &nick, const std::string &reason);
};

#endif
