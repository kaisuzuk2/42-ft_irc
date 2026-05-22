/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdUser.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-21 23:18:14 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-21 23:18:14 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands/CmdUser.hpp"
#include "Client.hpp"
#include "ft_ircd.hpp"

/*
RFC 1459
パラメータ:  <username> <hostname> <servername> <realname>

RFC 2812
パラメーター: <user> <mode> <unused> <realname>
※usermodeは今回実装しないため、modeパラメータは無視する

*/

CmdUser::CmdUser()
    : ACommand("USER", 4, 4, true)
{}

CmdUser::~CmdUser() {}

/*
FRC2812
user       =  1*( %x01-09 / %x0B-0C / %x0E-1F / %x21-3F / %x41-FF )
                ; NUL、CR、LF、" "、"@" を除く任意のオクテット
*/
bool CmdUser::_isValidUser(const std::string &user) const
{
    int c;

    if (user.empty())
        return (false);

    for (std::string::const_iterator i = user.begin(); i != user.end(); ++i)
    {
        c = static_cast<unsigned char>(*i);
        if (c >= 0x01 && c <= 0x09) continue ;
        if (c >= 0x0B && c <= 0x0C) continue ;
        if (c >= 0x0E && c <= 0x1F) continue ;
        if (c >= 0x21 && c <= 0x3F) continue ;
        if (c >= 0x41 && c <= 0xFF) continue ;
        return (false);
    }
    return (true);
}

void CmdUser::_execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params)
{
    const std::string &newreal = params[3]; // ### TODO: 定数化した方がいいかな
    std::string newuser;

    if (client._getUsername().empty())
    {
        newuser = params[0]; // ### TODO: 定数化した方がいいかな
        if (newuser.length() > FtIRCd::kMaxUserLen)
            newuser.erase(FtIRCd::kMaxUserLen);

        if (!this->_isValidUser(newuser))
        {
            client._writeNumeric(ERR_INVALIDUSERNAME, serverInstance._getServername(), newuser + " :Your username is not valid");
            return ;
        }
        client._setUsername(newuser);
        client._setRealname(newreal);
    }
    else
    {
       client._writeNumeric(ERR_ALREADYREGISTERED, serverInstance._getServername(), ":Unauthorized command (already registered)");
       return ; 
    }
    
    if (!client._isRegistered())
        serverInstance._checkRegister(client);
}





