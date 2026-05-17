/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdNick.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-17 00:40:13 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-17 00:40:13 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands/CmdNick.hpp"
#include "ft_ircd.hpp"
#include "Client.hpp"

CmdNick::CmdNick()
    : ACommand("NICK", 1, 0, true)
{}

CmdNick::~CmdNick() {}

void CmdNick::_execute(FtIRCd &serverInstance, Client &client, std::vector<std::string> &params)
{
    const std::string &newnick = params[0];
}