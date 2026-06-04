/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdMotd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-06-03 23:39:34 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-06-03 23:39:34 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdMotd.hpp"

/*
RFC 2812
パラメーター: [ <target> ]

[Note]
指定されたサーバー、または <target> が省略された場合は
現在のサーバーの「今日のメッセージ（Message Of The Day）」を取得するために使用されます。
*/

CmdMotd::CmdMotd() 
    : Acommand("MOTD", 0, 0, false)
{}

CmdMotd::~CmdMotd() {}

void CmdMotd::_execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params)
{
    if (!params.empty() && (serverInstance._getServername() != params[0]))
        return ;
    
}