/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdMotd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-06-03 23:39:34 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-06-03 23:39:34 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>

#include "commands/CmdMotd.hpp"

#include "ft_ircd.hpp"

/*
RFC 2812
パラメーター: [ <target> ]

[Note]
指定されたサーバー、または <target> が省略された場合は
現在のサーバーの「今日のメッセージ（Message Of The Day）」を取得するために使用されます。
*/

CmdMotd::CmdMotd() 
    : ACommand("MOTD", 0, 0, false)
{}

CmdMotd::~CmdMotd() {}

void CmdMotd::_execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params)
{
    if (!params.empty() && (serverInstance._getServername() != params[0]))
        return ;
    
    std::ifstream ifs(FtIRCd::kMotdPath);
    if (!ifs.is_open())
    {
        client._writeNumeric(ERR_NOMOTD, serverInstance._getServername(), ":MOTD File is missing");
        return ;
    }

    client._writeNumeric(RPL_MOTDSTART, serverInstance._getServername(), ":" + serverInstance._getServername() + " message of the day:");
    
    std::string line;
    while (std::getline(ifs, line))
        client._writeNumeric(RPL_MOTD, serverInstance._getServername(), ":" + line);
    
    client._writeNumeric(RPL_ENDOFMOTD, serverInstance._getServername(), "End of MOTD command");
}