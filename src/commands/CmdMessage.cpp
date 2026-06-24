/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdMessage.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 00:29:56 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/06/24 09:43:57 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands/CmdMessage.hpp"
#include "ft_ircd.hpp"

/*
RFC 1459
NOTCIE  パラメータ:  <nickname> <text>
PRIVMSG パラメータ:  <receiver>{,<receiver>} <text to be sent>

RFC 2812
NOTICE  パラメーター: <msgtarget> <text>
PRIVMSG パラメーター: <msgtarget> <text to be sent>

*/

/*
[Note]
RFC 2812
NOTICEとPRIVMSGの違いは、NOTICEメッセージに対して自動返信を送信してはならない（MUST NEVER）という点です。
このルールはサーバーにも適用されます。
サーバーはNOTICEを受信した際にクライアントへエラー返信を送信してはなりません（MUST NOT）。
[server]
inspircdではエラーを返す
solanum(libera.chat)ではエラーを返さない
*/


CmdMessage::CmdMessage(bool isNotice) 
    : ACommand(isNotice ? "NOTICE" : "PRIVMSG", 2, 2, false, true)
    , _isNotice(isNotice)
{}

CmdMessage::~CmdMessage() {}

void CmdMessage::_handleUserTarget(FtIRCd &serverInstance, Client &client,const std::string &nick, const std::string &msg)
{
    Client *target;

    target = serverInstance._getClients()._findByNick(nick, true);
    if (!target)
    {
        if (!this->_isNotice)
            client._writeNumeric(Numerics::NoSuchNick(nick), serverInstance._getServername());
        return ;
    }
    
    target->_send(":" + client._getPrefix() + " " + this->_getName() + " " + target->_getNick() + " :" + msg);
}

bool CmdMessage::_preMessageCheck(FtIRCd &serverInstance, Client &client, Channel &chan)
{
    if (chan._isModeSet(MODE_NO_EXTERNAL) && !chan._hasMember(&client))
    {
        if (!this->_isNotice)
            client._writeNumeric(ERR_CANNOTSENDTOCHAN, serverInstance._getServername(), chan._getName() + " :Cannot send to channel (+n)");
        return (false);
    }
    return (true);
}

void CmdMessage::_handleChannelTarget(FtIRCd &serverInstance, Client &client, const std::string &cname, const std::string &msg, bool operOnly)
{
    Channel *chan;

    chan = serverInstance._getChannels()._find(cname);
    if (!chan)
    {
        if (!this->_isNotice)
            client._writeNumeric(Numerics::NoSuchChannel(cname), serverInstance._getServername());
        return ;
    }

    if (!this->_preMessageCheck(serverInstance, client, *chan))
        return ;
    
    chan->_broadcast(":" + client._getPrefix() + " " + this->_getName() + " " + chan->_getName() + " :" + msg, &client, operOnly);

}

void CmdMessage::_execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params)
{
    const std::string &msg = params[1];
    std::vector<std::string> targets;

    targets = this->_splitByComma(params[0], true);

    if (msg.empty())
    {   
        if (!this->_isNotice)
            client._writeNumeric(ERR_NOTEXTTOSEND, serverInstance._getServername(), ":No text to send");
        return ;
    }

    for (std::vector<std::string>::const_iterator it = targets.begin(); it != targets.end(); ++it)
    {   
        const std::string &target = *it;
        size_t pos = 0;
        bool operOnly = false;

        while (pos < target.size() && ChannelManager::_isStatusPrefix(target[pos]))
        {
            operOnly = true;
            ++pos;
        }
        if (!target[pos])
        {
            if (!this->_isNotice)
                client._writeNumeric(ERR_NORECIPIENT, serverInstance._getServername(), "No recipient given (" + this->_getName() + ")");
            return ;   
        }
        if (ChannelManager::_isPrefix(target[pos])) 
            _handleChannelTarget(serverInstance, client, target.substr(pos), msg, operOnly);
        else
            _handleUserTarget(serverInstance, client, target, msg);
    }

}
