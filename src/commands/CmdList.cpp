/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdList.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-06-12 02:59:06 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-06-12 02:59:06 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands/CmdList.hpp"
#include "ChannelManager.hpp"
#include "Channel.hpp"

#include <string>
#include <map>
#include <sstream>

/*
RFC 1459
パラメータ:  [<channel>{,<channel>} [<server>]]

RFC 2812
パラメーター: [ <channel> *( "," <channel> ) [ <target> ] ]

[Note]
LISTコマンドはチャンネルとそのトピックを一覧表示するために使用されます。
<channel> パラメーターが使用された場合、そのチャンネルの状態のみが表示されます。
<target> パラメーターが指定された場合、リクエストはそのサーバーに転送され、そのサーバーが返信を生成します。
*/

CmdList::CmdList()
    : ACommand("LIST", 0, 0, false)
{}

CmdList::~CmdList() {}

void CmdList::_execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params)
{
    std::map<std::string, Channel *> channels = serverInstance._getChannels()._getChannels();
    
    if (params.empty())
    {
        for (std::map<std::string, Channel *>::const_iterator it = channels.begin(); it != channels.end(); ++it)
        {
            std::ostringstream oss;
            oss << it->second->_getName() 
            << " "
            << it->second->_getMemberSize()
            << " :"
            << it->second->_getTopic();
            client._writeNumeric(RPL_LIST, serverInstance._getServername(), oss.str());
        }        
    }
}