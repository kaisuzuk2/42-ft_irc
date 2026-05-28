/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdPart.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-28 00:33:47 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-28 00:33:47 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "comamnds/CmdPart.hpp"

/*
RFC 1459
パラメータ:  <channel>{,<channel>}

RFC 2812
パラメーター: <channel> *( "," <channel> ) [ <Part Message> ]
*/

CmdPart::CmdPart() 
    : ACommand("PART", 1, 2, false)
{}

CmdPart::~CmdPart() {}

void CmdPart::_partChannel(FtIRCd &serverInstance, Client &client, const std::string &cname, const std::string reason)
{
    Channel *ch;

    ch = server._getChannels()._find(cname);
}

void CmdPart::_execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params)
{
    std::string reason;
    std::string chanStr;
    std::string::size_type pos;
    std::vector<std::string> channels;

    reason = params.size() > 1 ? params[1] : "";

    // ### TODO: 共通の処理だからどこかで関数化すべきだね
    chanStr = params[0];
    while ((pos = chanStr.find(',')) != std::string::npos)
    {
        channels.push_back(chanStr.substr(0, pos));
        chanStr.erase(0, pos + 1);
    }
    channels.push_back(chanStr);

    for (size_t i = 0; i < channels.size(); ++i)
        _partChannel(server, client, channels[i], reason);
}