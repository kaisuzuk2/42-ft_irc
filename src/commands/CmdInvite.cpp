/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdInvite.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-30 22:22:37 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-30 22:22:37 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands/CmdInvite.hpp"

/*
RFC 1459
パラメータ:  <nickname> <channel>

RFC 2182
パラメーター: <nickname> <channel>

[Note]
パラメーター <nickname> は、対象チャンネル <channel> に招待される人物のニックネームです。
招待先のチャンネルが存在するか有効なチャンネルである必要はありません。
ただし、チャンネルが存在する場合、そのチャンネルのメンバーのみが他のユーザーを招待できます。
チャンネルに招待制フラグが設定されている場合、チャンネルオペレーターのみがINVITEコマンドを実行できます。
*/

CmdInvite::CmdInvite() 
    : ACommand("INVITE", 0, 0, false)
{}

CmdInvite::~CmdInvite() {}

void CmdInvite::_execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params)
{
    Channel *ch;
    Client *target;
    // invite
    // invite nicksample
    // パラメータが一つの場合無視する

    if (params.size() < 2)
    {
        // ### TODO: 招待されているリスト一覧を表示する
        client._writeNumeric(RPL_ENDOFINVITELIST, serverInstance._getServername(), " :End of INVITE list");
        return ;
    }

    const std::string &nick = params[0];
    const std::string &cname = params[1];

    ch = serverInstance._getChannels()._find(cname);
    if (!ch)
    {
        client._writeNumeric(ERR_NOSUCHCHANNEL, serverInstance._getServername(), cname + " :No such channel");
        return ;
    }

    target = serverInstance._getClients()._findByNick(nick);
    if (!target)
    {
        client._writeNumeric(ERR_NOSUCHNICK, serverInstance._getServername(), nick + " :No such nick");
        return ;
    }

    if (!ch->_hasMember(&client))
    {
        client._writeNumeric(ERR_NOTONCHANNEL, serverInstance._getServername(), ch->_getName() + " :You're not on that channel");
        return ;
    }

    

}