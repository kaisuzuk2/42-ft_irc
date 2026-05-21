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

#include "CmdUser.hpp"

/*
RFC 1459
パラメータ:  <username> <hostname> <servername> <realname>

RFC 2812
パラメーター: <user> <mode> <unused> <realname>
※usermodeは今回実装しないため、modeパラメータは無視する

*/

CmdUser::CmdUser()
    : ACommand("USER", 4, 4, true);
{}

/*
FRC2812
user       =  1*( %x01-09 / %x0B-0C / %x0E-1F / %x21-3F / %x41-FF )
                ; NUL、CR、LF、" "、"@" を除く任意のオクテット
*/
bool CmdUser::_isValidUser(const std::string &user) const
{

}

void CmdUser::_execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params)
{
    const std::string &newreal = params[3]; // ### TODO: 定数化した方がいいかな

    if (client._getUsername().empty())
    {
        std::string newuser = params[0]; // ### TODO: 定数化した方がいいかな
        if (newuser.length() > FtIRCd::kMaxUserLen)
            newuser.erase(FtIRCd::kMaxUserLen);
    }
    else
    {
       client._writeNumeric(ERR_ALREADYREGISTERED, serverInstance._getServername(), ":Unauthorized command (already registered)");
       return ; 
    }
}





