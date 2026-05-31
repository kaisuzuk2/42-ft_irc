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


[Note] RFC2188 4.2.2
チャンネルフラグ 'i' が設定されている場合、
新しいメンバーは、そのマスクが招待リスト（セクション4.3.2を参照）に一致するか、
チャンネルオペレーターから招待された場合にのみ受け入れられる。
このフラグはまた、INVITE コマンド（「IRC Client Protocol」[IRC-CLIENT]を参照）の使用を
チャンネルオペレーターに限定する。
*/

CmdInvite::CmdInvite() 
    : ACommand("INVITE", 0, 0, false)
{}

CmdInvite::~CmdInvite() {}

bool CmdInvite::_preInviteCheck(FtIRCd &serverInstance, Client &client, Channel *ch)
{
    if (ch->_isModeSet(MODE_INVITE_ONLY) && !ch->_isOper(&client))
    {
        client._writeNumeric(ERR_CHANOPRIVSNEEDED, serverInstance._getServername(), ch->_getName() + " :You're not channel operator");
        return (false);
    }
    return (true);
}

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

    if (ch->_hasMember(target))
    {
        client._writeNumeric(ERR_USERONCHANNEL, serverInstance._getServername(), target->_getNick() + " " + ch->_getName() + " :is already on channel");
        return ;
    }

    if (!this->_preInviteCheck(serverInstance, client, ch))
        return ;

    ch->_addInvite(target);
    target->_addInvitedChannel(ch);

    // ### TODO: オペレータにのみ送信するよう切り替えること
    ch->_broadcast(":" + serverInstance._getServername() + " " + "NOTICE " + ch->_getName() + ":*** " + client._getNick() + " invited " + target->_getNick() + " into the channel", NULL);
    
    target->_send(":" + client._getPrefix() + " INVITE " + target->_getNick() + " :" + ch->_getName());
    client._writeNumeric(RPL_INVITING, serverInstance._getServername(), target->_getNick() + " " + ch->_getName());        
}