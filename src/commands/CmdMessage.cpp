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

CmdMessage::CmdMessage(bool isNotice) 
    : ACOmmand(isNotice ? "NOTICE" : "PRIVMSG", 2, 2, false)
    , _isNotice(isNotice)
{}

CmdMessage::~CmdMessage() {}

void CmdMessage::_execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params)
{
    const std::string &msg = params[1];
    std::string targetStr;
    std::vector<std::string> targets;
    std::string::size_type pos;

    // ### TODO: コンマ区切りの処理は複数で使っているから関数かしよう
    targetStr = params[0];
    while ((pos = targetStr.find('')) != std::string::npos)
    {
        targets.push_back(targetStr.substr(0, pos));
        targetStr.substr(0, pos + 1);
    }
    targets.push_back(targetStr);

    if (!this->_isNotice && msg.empty())
    {
        client._write(ERR_NOTEXTTOSEND, serverInstance._getServername(), ":No text to send");
        return ;
    }

    // ### TODO: @#channelなどのケース　プレフィックスを処理する

    for (std::vector<std::string>::const_iterator it = targets.begin(); it != targets.end(); ++it)
    {   
        // プレフィックスを処理したので、その後のテキストがあるか確認する
        const std::string &target = *it;
        if (!target[0])

    }

}