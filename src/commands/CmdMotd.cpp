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

CmdMotd::CmdMotd() 
    : Acommand("MOTD", 0, 0, false)
{}

CmdMotd::~CmdMotd() {}

void CmdMotd::_execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params)
{

}