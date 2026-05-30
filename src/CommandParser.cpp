/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandParser.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-15 03:07:50 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-15 03:07:50 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandParser.hpp"
#include "commands/CmdPass.hpp"
#include "commands/CmdNick.hpp"
#include "commands/CmdUser.hpp"
#include "commands/CmdJoin.hpp"
#include "commands/CmdPart.hpp"
#include "commands/CmdQuit.hpp"
#include "commands/CmdMessage.hpp"

#include "ft_ircd.hpp"
#include "Client.hpp"
#include <iostream>

#include <algorithm>

CommandParser::CommandParser() 
{
    this->_commands["PASS"] = new CmdPass();
    this->_commands["NICK"] = new CmdNick();
    this->_commands["USER"] = new CmdUser();
    this->_commands["JOIN"] = new CmdJoin();
    this->_commands["PART"] = new CmdPart();
    this->_commands["QUIT"] = new CmdQuit();
    this->_commands["PRIVMSG"] = new CmdMessage(false);
    this->_commands["NOTICE"] = new CmdMessage(true);
}

CommandParser::~CommandParser() 
{
    std::map<std::string, ACommand*>::iterator it = this->_commands.begin();
    while (it != this->_commands.end())
    {
        delete it->second;
        ++it;
    }
    this->_commands.clear();
}

std::vector<std::string> CommandParser::_split(const std::string &line, size_t max_params)
{
    std::vector<std::string> params;
    std::string::size_type i;
    std::string::size_type end;

    i = 0;
    while (i < line.size())
    {
        if (line[i] == ' ')
        {
            ++i;
            continue ;
        }
        if (line[i] == ':') 
        {
            params.push_back(line.substr(i + 1));
            break;
        }

        end = line.find(' ', i);
        if (end == std::string::npos)
        {
            params.push_back(line.substr(i));
            break;
        }
        params.push_back(line.substr(i, end - i));
        i = end + 1;

        if (max_params && params.size() == max_params)
        {
            params.back() += " " + line.substr(i);
            break;
        }
    }
    return (params);
}


/*
### TODO: noticeの場合引数が足りない場合もエラーを出さないようにする
*/
void CommandParser::_process(FtIRCd &serverInstance, Client &client, const std::string &line)
{
    std::vector<std::string> tokens;
    std::string cmd;
    size_t sp;
    std::vector<std::string> params;
    std::string args;

    if (line.empty())
        return ;
    
    tokens = this->_split(line);
    if (tokens.empty())
        return ;

    cmd = tokens[0];
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);

    std::map<std::string, ACommand *>::iterator it = this->_commands.find(cmd);
    if (it == this->_commands.end())
    {
        // 登録が済んでいたらエラーにする
        if (client._isRegistered())
        {
            // client._send(": " + serverInstance._getServername() + " 421 " + client._getNick() + " " + cmd + " :Unknown commmand");
            client._writeNumeric(ERR_UNKNOWNCOMMAND, serverInstance._getServername(), ":Unknown commmand");
        }
        return ;
    }

    ACommand *command = it->second;

    // ### TODO: command分 +1している　改善しよう
    // std::vector<std::string> params = this->_split(line, command->_getMaxParams() + 1);
    // params.erase(params.begin());
    sp = line.find(' ');
    if (sp != std::string::npos)
    {
        args = line.substr(sp + 1);
        params = this->_split(args, command->_getMaxParams());
    }
    // 登録前に使えない
    if (!command->_getWorksBeforeReg() && !client._isRegistered())
    {
        // client._send(": " + serverInstance._getServername() + " 451 " + client._getNick() + " :You have not registered");
        client._writeNumeric(ERR_NOTREGISTERED, serverInstance._getServername(), ":You have not registered");
        return;
    }

    // min paramチェック
    if (params.size() < command->_getMinParams())
    {
        // client._send(": " + serverInstance._getServername() + " 461 " + client._getNick() + " " + cmd + " :Not enough parameters.");
        client._writeNumeric(ERR_NEEDMOREPARAMS, serverInstance._getServername(), cmd + " :Not enough parameters.");
        return ;
    }
    
    command->_execute(serverInstance, client, params);
}