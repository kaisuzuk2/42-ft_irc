/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdKick.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-30 01:35:09 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-30 01:35:09 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdKick.hpp"

/*
RFC 1459
パラメータ:  <channel> <user> [<comment>]

RFC 2812
パラメーター: <channel> *( "," <channel> ) <user> *( "," <user> )
             [<comment>]

[Note]
メッセージが構文的に正しいためには、
チャンネルパラメーターが1つでユーザーパラメーターが複数、
またはチャンネルパラメーター数とユーザーパラメーター数が同数でなければなりません（MUST）。
「comment」が指定された場合、
KICKを実行したユーザーのニックネームというデフォルトメッセージの代わりにそれが送信されます。
*/

CmdKick::CmdKick() 
    : ACommand("KICK", 2, 3, false)
{}

CmdKick::CmdKick() {}


// ### TODO: kick #a,,,#c 連続する,は空文字になる　それはスキップする
void CmdKick::_execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params)
{
    std::vector<std::string> channels;
    std::vector<std::string> users;
    std::string::size_type pos;
    std::string chanStr;
    std::string userStr;

    // ### TOOD: コンマ区切りの分割は関数化すること
    chanStr = params[0];
    while ((pos = chanStr.find(',')) != std::string::npos)
    {
        channels.push_back(chanStr.substr(0, pos));
        chanStr.erase(0, pos + 1);
    }
    channels.push_back(chanStr);

    userStr = params[1];
    while ((pos = userStr.find(',')) != std::string::npos)
    {
        users.push_back(userStr.substr(0, pos));
        userStr.erase(0, pos + 1);
    }
    users.push_back(userStr);

    
}