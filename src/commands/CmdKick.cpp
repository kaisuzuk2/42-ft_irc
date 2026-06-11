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

#include "commands/CmdKick.hpp"
#include "Channel.hpp"
#include "ft_ircd.hpp"

/*
RFC 1459 (inspircd)
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

CmdKick::~CmdKick() {}


void CmdKick::_kickUser(FtIRCd &serverInstance, Client &client, const std::string &cname, const std::string &nick, const std::string &reason)
{
    Channel *ch;
    Client *target;

    ch = serverInstance._getChannels()._find(cname);
    if (!ch)
    {
        client._writeNumeric(ERR_NOSUCHCHANNEL, serverInstance._getServername(), cname + " :No such channel");
        return ;
    }

    target = serverInstance._getClients()._findByNick(nick, true);
    if (!target)
    {
        client._writeNumeric(ERR_NOSUCHNICK, serverInstance._getServername(), nick + " :No such nick");
        return ;
    }

    if (!ch->_hasMember(&client))
    {
        client._writeNumeric(ERR_NOTONCHANNEL, serverInstance._getServername(), ch->_getName() + " :You're not on that channel");
        return ;
    }

    if (!ch->_hasMember(target))
    {
        client._writeNumeric(ERR_USERNOTINCHANNEL, serverInstance._getServername(), target->_getNick()  + " " + ch->_getName() + " :They aren't on that channel");
        return ;
    }

    if (!ch->_isOper(&client))
    {
        client._writeNumeric(ERR_CHANOPRIVSNEEDED, serverInstance._getServername(), ch->_getName() + " :You're not channel operator");
        return ;
    }


    ch->_broadcast(":" + client._getPrefix() + " KICK " + ch->_getName() + " " + target->_getNick() + " :" + reason, NULL, false);

    ch->_removeMember(target);
    target->_leaveChannel(ch);
    if (ch->_isEmpty())
        serverInstance._getChannels()._remove(cname);    
}

void CmdKick::_execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params)
{
    std::vector<std::string> channels;
    std::vector<std::string> users;

    const std::string reason = params.size() > 2 ? params[2] : client._getNick();

    channels = this->_splitByComma(params[0], true);
    users = this->_splitByComma(params[1], true);

    if (channels.size() == 1)
    {
        for (size_t i = 0; i < users.size(); ++i)
            _kickUser(serverInstance, client, channels[0], users[i], reason);
    }
    else if (channels.size() == users.size())
    {
        for (size_t i = 0; i < users.size(); ++i)
            _kickUser(serverInstance, client, channels[i], users[i], reason);
    }
    else
        client._writeNumeric(ERR_NEEDMOREPARAMS, serverInstance._getServername(), "KICK :Not enough parameters");
}