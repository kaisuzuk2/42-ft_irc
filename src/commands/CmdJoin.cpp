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

channels.cpp
https://github.com/inspircd/inspircd/blob/5b5be2721fe408ffc13c0558b93037e6994461ff/src/channels.cpp#L166
*/

CmdJoin::CmdJoin()
    : ACommand("JOIN", 1, 2, false, false)
{}

CmdJoin::~CmdJoin() {}

void CmdJoin::_partAllChannels(FtIRCd &serverInstance, Client &client)
{
    const std::set<Channel *> channels = client._getChannels();
    for (std::set<Channel *>::const_iterator it = channels.begin(); it != channels.end(); ++it)
    {
        std::vector<std::string> params;
        params.push_back((*it)->_getName());
        serverInstance._getParser()._callExecute(serverInstance, client, "PART", params);
    } 
}

/*
RFC2811 2.1
スペース（' '）、コントロールG（^G またはASCII 7）、
カンマ（','、プロトコルにおいてリスト項目の区切り文字として使用される）
を含んではならない
*/
bool CmdJoin::_isValidChannelName(const std::string &name) const
{
    if (name.empty() || name.length() > FtIRCd::kMaxChanLen)
        return (false);

    if (!ChannelManager::_isPrefix(name[0]))
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

bool CmdJoin::_preJoinCheck(FtIRCd &serverInstance, Client &client, const std::string &cname, Channel *ch, const std::string &key)
{
    // 上限数チェック
    if (client._getChannelSize() >= FtIRCd::kMaxChannels)
    {
        client._writeNumeric(ERR_TOOMANYCHANNELS, serverInstance._getServername(), ch ? ch->_getName() : cname + " :You have joined too many channels");
        return (false);
    }

    // 新規チャンネル
    if (!ch)
        return (true);

    // キーチェック
    if (!ch->_getKey().empty() && ch->_getKey() != key)
    {
        client._writeNumeric(ERR_BADCHANNELKEY, serverInstance._getServername(), ch->_getName() + " :Cannot join channel (+k)");
        return (false);
    }

    // 招待チェック
    if (ch->_isModeSet(MODE_INVITE_ONLY) && !ch->_isInvited(&client))
    {
        client._writeNumeric(ERR_INVITEONLYCHAN, serverInstance._getServername(), ch->_getName() + " :Cannot join channel (+i)");
        return (false);
    }

    // 人数制限値チェック
    if (ch->_isModeSet(MODE_LIMIT) && ch->_getMemberSize() >= ch->_getLimit())
    {
        client._writeNumeric(ERR_CHANNELISFULL, serverInstance._getServername(), ch->_getName() + " :Cannot join channel (+l)");
        return (false);
    }

    return (true);
}

// ### TODO: これらはchannelクラスにあるべきかな
void CmdJoin::_joinChannel(FtIRCd &serverInstance, Client &client, const std::string &cname, const std::string &key)
{
    Channel *ch;
    bool isNew;

    ch = serverInstance._getChannels()._find(cname);
    isNew = (ch == NULL);

    if (!this->_preJoinCheck(serverInstance, client, cname, ch, key))
        return ;
    if (isNew)
        ch = serverInstance._getChannels()._create(cname); 
    else
    {
        /* Already on the channel */
        if (ch->_hasMember(&client))
            return ;
    }

    // TODO: セットでやるようにした方がいいかね
    // TODO: whois <nick> 最新のチャンネルから表示される　順番があるね
    ch->_addMember(&client, isNew);
    client._joinChannel(ch);
    ch->_removeInvite(&client);
    client._removeInvitedChannel(ch);


    ch->_broadcast(":" + client._getPrefix() + " JOIN :" + cname, NULL, false);

    if (!ch->_getTopic().empty())
        ch->_showTopic(client, serverInstance._getServername());

    // TODO: onpostjoin
    ch->_sendNames(client, serverInstance._getServername());
    client._writeNumeric(RPL_ENDOFNAMES, serverInstance._getServername(), ch->_getName() + " :End of NAMES list" );

}

void CmdJoin::_execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params)
{
    std::vector<std::string> channels;
    std::vector<std::string> keys;

    if (params[0] == "0")
    {
        this->_partAllChannels(serverInstance, client);
        return ;
    }

    channels = this->_splitByComma(params[0], true);
    if (params.size() > 1)
        keys = this->_splitByComma(params[1], false);

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