/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdQuit.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-28 03:11:41 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-28 03:11:41 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands/CmdQuit.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "ft_ircd.hpp"

CmdQuit::CmdQuit()
    : ACommand("QUIT", 0, 1, true)
{}

CmdQuit::~CmdQuit() {}

// ### TODO: quitmsgの長さ制限
void CmdQuit::_execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params)
{
    std::string quitmsg;
    std::string errmsg;

    // ### TODO: いい感じにできないかな
    quitmsg = params.empty() ? "Client exited" : params[0];
    errmsg = params.empty() ? "Client exited" : "Quit :" + params[0];

    client._send("ERROR :Closing link: (" + client._getPrefix() + ") [" +errmsg + "]");
    client._flushSendBuf();

    client._setQuitting();
    serverInstance._quitUser(client, quitmsg);
    serverInstance._disconnectClient(client._getFd());
}