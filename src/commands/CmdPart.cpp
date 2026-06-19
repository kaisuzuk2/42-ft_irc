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

#include <sstream>

#include "commands/CmdPart.hpp"
#include "Channel.hpp"
#include "ft_ircd.hpp"

/*
RFC 1459
パラメータ:  <channel>{,<channel>}

RFC 2812
パラメーター: <channel> *( "," <channel> ) [ <Part Message> ]

[Note]
PARTコマンドを送信したユーザーを、
パラメーター文字列に列挙されたすべてのチャンネルのアクティブメンバーリストから削除します。
「Part Message」が指定された場合、デフォルトのメッセージ（ニックネーム）の代わりにそれが送信されます。
このリクエストは常にサーバーによって許可されます。
サーバーはターゲットのリスト形式の引数を解析できなければなりません（MUST）が、
クライアントへPARTメッセージを送信する際にリストを使用するべきではありません（SHOULD NOT）。
*/


CmdPart::CmdPart() 
    : ACommand("PART", 1, 2, false, true)
{}

CmdPart::~CmdPart() {}

void CmdPart::_partChannel(FtIRCd &serverInstance, Client &client, const std::string &cname, const std::string &reason)
{
    Channel *ch;

    ch = serverInstance._getChannels()._find(cname);
    if (!ch)
    {
        client._writeNumeric(Numerics::NoSuchChannel(cname), serverInstance._getServername());
        return ;
    }
    if (!ch->_hasMember(&client))
    {
        client._writeNumeric(Numerics::NotOnChannel(ch->_getName()), serverInstance._getServername());
        return ;
    }


    std::ostringstream msg;
    msg << ":"
        << client._getPrefix()
        << " "
        << "PART"
        << " "
        << cname
        << " "
        << ":";
    if (!reason.empty())
        msg << reason;
    else
        msg << client._getNick();

    ch->_broadcast(msg.str(), NULL, false);

    ch->_removeMember(&client);
    client._leaveChannel(ch);
    if (ch->_isEmpty())
        serverInstance._getChannels()._remove(cname);
}

void CmdPart::_execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params)
{
    std::string reason;
    std::vector<std::string> channels;

    reason = params.size() > 1 ? params[1] : "";

    channels = this->_splitByComma(params[0], true);

    if (channels.empty())
    {
        client._writeNumeric(Numerics::NoSuchChannel(""), serverInstance._getServername());
        return ;
    }

    for (size_t i = 0; i < channels.size(); ++i)
        _partChannel(serverInstance, client, channels[i], reason);
}