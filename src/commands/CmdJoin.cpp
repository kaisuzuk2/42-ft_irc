/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdJoin.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-24 01:52:35 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-24 01:52:35 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands/CmdJoin.hpp"

/*

RFC1459
パラメータ:  <channel>{,<channel>} [<key>{,<key>}]
チャンネル文字数: 200文字

RFC2812
パラメーター: ( <channel> *( "," <channel> ) [ <key> *( "," <key> ) ] )
             / "0"
このメッセージは特別な引数（"0"）を受け付けます。
これは現在参加しているすべてのチャンネルを退出するための特別なリクエストです。
サーバーはこのメッセージを、ユーザーが参加しているすべてのチャンネルに対してPARTコマンドを送信したかのように処理します。

RFC2811
チャンネル文字数: 50文字
チャンネル名は大文字・小文字を区別しない。
*/

CmdJoin::CmdJoin()
    : ACommand("JOIN", 1, 2, false)
{}

/*
RFC2811 2.1
スペース（' '）、コントロールG（^G またはASCII 7）、カンマ（','、プロトコルにおいてリスト項目の区切り文字として使用される）
を含んではならない（SHALL NOT）
*/
bool CmdJoin::_isValidChannelName(const std::string &name)
{
    if (name.empty() || name.length() > FtIRCd::kMaxChanLen)
        return (false);

    if (!this->_isPrefix(name[0]))
        return (false);

    std::string::const_iterator it = name.begin();
    ++it; // prefix
    for (; it != name.end(); ++it)
    {
        switch(*it)
        {
            case 0x07: // BELL 
            case 0x20: // SPACE
            case 0x2C: // COMMA
                return (false);
        }
    }
    return (true);
}

bool CmdJoin::_isPrefix(unsigned char prefix) const
{
    return prefix == '#';
}

