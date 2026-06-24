/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdNames.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 00:55:29 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/06/24 09:44:16 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ircd.hpp"
#include "Channel.hpp"
#include "commands/CmdNames.hpp"

/*
RFC 1459
パラメータ:  [<channel>{,<channel>}]

RFC 2812
パラメーター: [ <channel> *( "," <channel> ) [ <target> ] ]

[Note]
NAMESコマンドを使用することで、ユーザーは自分に見えるすべてのニックネームを一覧表示できます。
何が見えて何が見えないかの詳細については、「Internet Relay Chat: Channel Management」[IRC-CHAN] を参照してください。
<channel> パラメーターは情報を返すチャンネルを指定します。無効なチャンネル名に対するエラー返信はありません。
<channel> パラメーターが指定されない場合、すべてのチャンネルとその参加者の一覧が返されます。(inspircdでは、サーバーの負荷が高い処理になるため、処理しない)
このリストの末尾に、いずれのチャンネルにも参加していないか、
可視チャンネルにいない可視ユーザーの一覧が「*」チャンネルにいるものとして表示されます。
<target> パラメーターが指定された場合、リクエストはそのサーバーに転送され、そのサーバーが返信を生成します。
<target> パラメーターにはワイルドカードが使用できます。
*/

CmdNames::CmdNames() 
    : ACommand("NAMES", 0, 0, false, false)
{}

CmdNames::~CmdNames() {}

void CmdNames::_execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params)
{
    const std::string &servername = serverInstance._getServername();
    if (params.empty())
    {
        const std::map<std::string, Channel *> channels = serverInstance._getChannels()._getChannels();
        for (std::map<std::string, Channel *>::const_iterator it = channels.begin(); it != channels.end(); ++it)
        {
            it->second->_sendNames(client, servername);
        }

        const std::map<int, Client *> clients = serverInstance._getClients()._getClients();
        std::string nameList;
        for (std::map<int, Client *>::const_iterator it = clients.begin(); it != clients.end(); ++it)
        {
            if (!it->second->_isRegistered() || it->second->_getChannelSize())
                continue ;
            nameList += it->second->_getNick() + " ";
        }
        if (!nameList.empty())
            client._writeNumeric(RPL_NAMREPLY, servername, "* * :" + nameList);
        
        client._writeNumeric(RPL_ENDOFNAMES, servername, "* :End of NAMES list");
        return ;
    }   
    
    std::vector<std::string> cnames = this->_splitByComma(params[0], true);
    for (size_t i = 0; i < cnames.size(); ++i)
    {
        Channel *ch = serverInstance._getChannels()._find(cnames[i]);
        if (ch)
            ch->_sendNames(client, servername);
    }
    client._writeNumeric(RPL_ENDOFNAMES, servername, params[0] + " :End of NAMES list");
}
