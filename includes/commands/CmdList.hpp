/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdList.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-06-12 02:56:55 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-06-12 02:56:55 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDLIST_HPP
# define CMDLIST_HPP

#include "ft_ircd.hpp"
#include "ACommand.hpp"

class CmdList: public ACommand
{
    public:
        CmdList();
        ~CmdList();

        void    _execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params);
    
    private:
        std::string     _makeChannelInfo(const Channel *ch) const;
};

#endif