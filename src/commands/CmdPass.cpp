/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdPass.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-16 23:02:45 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-16 23:02:45 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands/CmdPass.hpp"
#include "ft_ircd.hpp"
#include "Client.hpp"

CmdPass::CmdPass() 
    : ACommand("PASS", 1, 1, true)
{};

CmdPass::~CmdPass() {}

void CmdPass::_execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params)
{
    if (client._isRegistered())
    {
        client._send(":" + serverInstance._getServername() + " 462 " + client._getNick() + ": Unauthorized command (already registered)");
        return ;
    }
    client._setPassword(params[0]);
}