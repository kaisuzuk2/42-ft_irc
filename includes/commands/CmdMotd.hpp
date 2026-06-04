/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdMotd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-06-03 23:37:57 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-06-03 23:37:57 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDMOTD_HPP
# define CMDMOTD_HPP

#include "ACommand.hpp"

class CmdMotd: public ACommand
{
    public :
        CmdMotd();
        ~CmdMotd();

        void    _execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params);
};

#endif