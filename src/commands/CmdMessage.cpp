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

