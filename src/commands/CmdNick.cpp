/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdNick.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-17 00:40:13 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-17 00:40:13 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands/CmdNick.hpp"
#include "ft_ircd.hpp"
#include "Client.hpp"

CmdNick::CmdNick()
    : ACommand("NICK", 1, 0, true)
{}

CmdNick::~CmdNick() {}

bool CmdNick::_isLetter(const char c) const 
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

bool CmdNick::_isSpecial(const char c) const 
{
    return ((c >= 0x5B && c <= 0x60) || (c >= 0x7B && c <= 0x7D));
}

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

void CmdNick::_execute(FtIRCd &serverInstance, Client &client, std::vector<std::string> &params)
{
    const std::string &newnick = params[0];

    if (newnick.empty())
    {
        client._send(":" + serverInstance._getServername() + " 431 " + client._getNick() + " :No nickname given");
        return ;
    }

    if (!this->_isValidNick(newnick))
    {
        client._send(":" + serverInstance._getServername() + " 432 " + client._getNick() + " " + newnick + " :Erroneous nickname");
        return ;
    }
}