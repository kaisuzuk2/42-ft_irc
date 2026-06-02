/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdMessage.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-29 00:29:56 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-29 00:29:56 by kaisuzuk         ###   ########.fr       */
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

### TODO: receiverのマスク(ワイルドカード)
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


/*
### TODO: findByNick
登録済みのもののみチェックする必要があるかも
チャンネルの大文字小文字のエラーメッセージ
*/
CmdMessage::CmdMessage(bool isNotice) 
    : ACommand(isNotice ? "NOTICE" : "PRIVMSG", 2, 2, false)
    , _isNotice(isNotice)
{}

CmdMessage::~CmdMessage() {}

void CmdMessage::_handleUserTarget(FtIRCd &serverInstance, Client &client,const std::string &nick, const std::string &msg)
{
    Client *target;
    std::string cmdName;

    target = serverInstance._getClients()._findByNick(nick); // ### TODO: 登録が完了しているかチェックしないと
    if (!target)
    {
        if (!this->_isNotice)
            client._writeNumeric(ERR_NOSUCHNICK, serverInstance._getServername(), nick + " :No such nick");
        return ;
    }
    
    cmdName = this->_isNotice ? "NOTICE" : "PRIVMSG"; // ### TODO: これ関数化しよう
    target->_send(":" + client._getPrefix() + " " + cmdName + " " + target->_getNick() + " :" + msg);
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

void CmdMessage::_handleChannelTarget(FtIRCd &serverInstance, Client &client, const std::string &cname, const std::string &msg)
{
    Channel *chan;
    std::string cmdName;

    chan = serverInstance._getChannels()._find(cname);
    if (!chan)
    {
        if (!this->_isNotice)
            client._writeNumeric(ERR_NOSUCHCHANNEL, serverInstance._getServername(), cname + " :No such channel");
        return ;
    }

    if (!this->_preMessageCheck(serverInstance, client, *chan))
        return ;
    
    // ### TODO: 関数にした方が良さそう
    cmdName = this->_isNotice ? "NOTICE" : "PRIVMSG";
    chan->_broadcast(":" + client._getPrefix() + " " + cmdName + " " + chan->_getName() + " :" + msg, &client);

}

// ### TODO: #a,,#bとかのケース
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

    // ### TODO: @#channelなどのケース　プレフィックスを処理する

    for (std::vector<std::string>::const_iterator it = targets.begin(); it != targets.end(); ++it)
    {   
        // プレフィックスを処理したので、その後のテキストがあるか確認する
        const std::string &target = *it;
        if (!target[0])
        {
            if (!this->_isNotice)
                client._writeNumeric(ERR_NORECIPIENT, serverInstance._getServername(), "No recipient given (" + this->_getName() + ")");
            return ;   
        }
        if (target[0] == '#') // ### TODO: cmdjoinに定義しているが、チャンネルマネージャークラスにあるべきかも
            _handleChannelTarget(serverInstance, client, target, msg);
        else
            _handleUserTarget(serverInstance, client, target, msg);
    }

}