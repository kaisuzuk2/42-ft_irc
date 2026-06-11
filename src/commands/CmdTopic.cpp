/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdTopic.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-31 01:15:00 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-31 01:15:00 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands/CmdTopic.hpp"

/*
RFC 1459
パラメータ:  <channel> [<topic>]

RFC 2812
パラメーター: <channel> [ <topic> ]

[Note]
TOPICコマンドはチャンネルのトピックを変更または表示するために使用されます。
<topic> が指定されていない場合、チャンネル <channel> のトピックが返されます。
<topic> パラメーターが指定された場合、
そのチャンネルのトピックが変更されます（リクエストしたユーザーにその操作が許可されている場合）。
<topic> パラメーターが空文字列の場合、そのチャンネルのトピックが削除されます。
*/

CmdTopic::CmdTopic()
    : ACommand("TOPIC", 1, 2, false)
{}

CmdTopic::~CmdTopic() {}

void CmdTopic::_execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params)
{
    const std::string &cname = params[0];
    Channel *ch;

    ch = serverInstance._getChannels()._find(cname);
    if (!ch)
    {
        // client._writeNumeric(ERR_NOSUCHCHANNEL, serverInstance._getServername(), cname + " :No such channel");
        client._writeNumeric(Numerics::NoSuchChannel(cname), serverInstance._getServername());
        return ;
    }

    // topic表示
    // ### TODO: トピックが設定されていないかどうかをここでやるかshowtopicでやるのがいいか
    if (params.size() == 1)
    {
        if (ch->_getTopic().empty())
            client._writeNumeric(RPL_NOTOPIC, serverInstance._getServername(), ch->_getName() + " :No topic is set");
        else
            ch->_showTopic(client, serverInstance._getServername());
        return ;
    }

    // topic設定
    if (!ch->_hasMember(&client))
    {
        // client._writeNumeric(ERR_NOTONCHANNEL, serverInstance._getServername(), ch->_getName() + " :You're not on that channel");
        client._writeNumeric(Numerics::NotOnChannel(ch->_getName()), serverInstance._getServername());
        return ;
    }

    if (ch->_isModeSet(MODE_TOPIC_OP) && !ch->_isOper(&client))
    {
        // client._writeNumeric(ERR_CHANOPRIVSNEEDED, serverInstance._getServername(), ch->_getName() + " :You're not channel operator");
        client._writeNumeric(Numerics::ChanOpPrivsNeeded(ch->_getName()), serverInstance._getServername());
        return ;
    }

    const std::string &t = params[1];
    // ### TODO: 長さチェックするか考える
    if (ch->_getTopic() != t)
        ch->_setTopic(t, client._getPrefix(), std::time(NULL));
}

