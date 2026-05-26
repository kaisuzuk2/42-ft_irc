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
チャンネルの同時参加数: 10(推奨)


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

CmdJoin::~CmdJoin() {}

/*
RFC2811 2.1
スペース（' '）、コントロールG（^G またはASCII 7）、カンマ（','、プロトコルにおいてリスト項目の区切り文字として使用される）
を含んではならない
*/
bool CmdJoin::_isValidChannelName(const std::string &name) const
{
    if (name.empty() || name.length() > FtIRCd::kMaxChanLen)
        return (false);

    if (!this->_isPrefix(name[0]))
        return (false);

    std::string::const_iterator it = name.begin() + 1; // prefix
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

bool CmdJoin::_preJoinCheck(FtIRCd &serverInstance, Client &client, Channel *ch, const std::string &cname, const std::string &key)
{
    // 上限数チェック
    if (client._getChannelSize() >= FtIRCd::kMaxChannels)
    {
        client._writeNumeric(ERR_TOOMANYCHANNELS, serverInstance._getServername(), cname + " :You have joined too many channels");
        return (false);
    }

    // 新規チャンネル
    if (!ch)
        return (true);

    // キーチェック
    if (!ch->_getKey().empty() && ch->_getKey() != key)
    {
        client._writeNumeric(ERR_BADCHANNELKEY, serverInstance._getServername(), cname + " :Cannot join channel (+k)");
        return (false);
    }

    // ###  TODO
    // 招待チェック

    // 人数制限値チェック

    return (true);
}

// ### TODO: これらはchannelクラスにあるべきかな

#include <iostream>
void CmdJoin::_joinChannel(FtIRCd &serverInstance, Client &client, const std::string &cname, const std::string &key)
{
    Channel *ch;
    bool isNew;

    ch = serverInstance._getChannels()._find(cname);
    isNew = (ch == NULL);

    if (!this->_preJoinCheck(serverInstance, client, ch, cname, key))
        return ;
    if (isNew)
        ch = serverInstance._getChannels()._create(cname); 
    else
    {
        /* Already on the channel */
        if (ch->_hasMember(&client))
            return ;
    }

    // セットでやるよおうにした方がいいかね
    ch->_addMember(&client, isNew);
    client._joinChannel(ch);

    ch->_broadcast(":" + client._getPrefix() + " JOIN :" + cname, NULL);
}

void CmdJoin::_execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params)
{
    std::string chanStr;
    std::string keyStr;
    std::vector<std::string> channels;
    std::vector<std::string> keys;
    std::string::size_type pos;

    chanStr = params[0];
    while ((pos = chanStr.find(',')) != std::string::npos)
    {
        channels.push_back(chanStr.substr(0, pos));
        chanStr.erase(0, pos + 1);
    }
    channels.push_back(chanStr);

    keyStr = params.size() > 1 ? params[1] : "";
    while ((pos = keyStr.find(',')) != std::string::npos)
    {
        keys.push_back(keyStr.substr(0, pos));
        keyStr.erase(0, pos + 1);
    }
    if (!keyStr.empty())
        keys.push_back(keyStr);

    for (size_t i = 0; i < channels.size(); ++i)
    {
        const std::string channel = channels[i];
        const std::string key = i < keys.size() ? keys[i] : "";

        if (!this->_isValidChannelName(channel))
        {
            client._writeNumeric(ERR_BADCHANMASK, serverInstance._getServername(), channel + " :Invalid channel name"); // message from inspircd
            continue ;
        }
        this->_joinChannel(serverInstance, client, channel, key);
    }
}