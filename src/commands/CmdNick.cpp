/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdNick.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 00:40:13 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/06/24 09:44:26 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands/CmdNick.hpp"
#include "ft_ircd.hpp"
#include "Client.hpp"

/*
RFC 1459
パラメータ:  <nickname> [ <hopcount> ]

RFC 2812
パラメーター: <nickname>

[Note]
NICKコマンドは、ユーザーにニックネームを付けるか、既存のニックネームを変更するために使用されます。
*/

CmdNick::CmdNick()
    : ACommand("NICK", 1, 0, true, true)
{}

CmdNick::~CmdNick() {}

bool CmdNick::_isLetter(int c) const 
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

bool CmdNick::_isSpecial(int c) const 
{
    return ((c >= 0x5B && c <= 0x60) || (c >= 0x7B && c <= 0x7D));
}

/*
nickname   =  ( letter / special ) *8( letter / digit / special / "-" )
letter     =  %x41-5A / %x61-7A       ; A-Z / a-z
digit      =  %x30-39                 ; 0-9
special    =  %x5B-60 / %x7B-7D
                 ; "[", "]", "\", "`", "_", "^", "{", "|", "}"
*/

bool CmdNick::_isValidNick(const std::string &n) const 
{
    if (n.empty() || n.length() > FtIRCd::kMaxNickLen)
        return (false);

    if (!this->_isLetter(n[0]) && !this->_isSpecial(n[0]))
        return (false);
    for (std::string::const_iterator i = n.begin() + 1; i != n.end(); ++i)
    {
        if (!this->_isLetter(*i) && !std::isdigit(*i) && !this->_isSpecial(*i) && *i != '-')
            return (false);
    }
    return (true);
}

void CmdNick::_execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params)
{
    const std::string &newnick = params[0];

    if (newnick.empty())
    {
        client._writeNumeric(ERR_NONICKNAMEGIVEN, serverInstance._getServername(), ":No nickname given");
        return ;
    }

    if (!this->_isValidNick(newnick))
    {
        client._writeNumeric(ERR_ERRONEUSNICKNAME, serverInstance._getServername(), newnick + " :Erroneous nickname");
        return ;
    }

    if (!client._changeNick(newnick, serverInstance._getClients(), serverInstance._getServername()))
        return ;
    
    if (!client._isRegistered())
        serverInstance._checkRegister(client);
}
