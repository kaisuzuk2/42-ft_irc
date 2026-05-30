/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdInvite.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-30 22:20:57 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-30 22:20:57 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDINVITE_HPP
# define CMDINVITE_HPP

#include "ACommand.hpp"

class CmdInvite: public ACommand
{
    CmdInvite();
    ~CmdInvite();

    void    _execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params);
};

#endif