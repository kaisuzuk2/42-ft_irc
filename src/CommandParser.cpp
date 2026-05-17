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

#include "ft_ircd.hpp"
#include "Client.hpp"
#include <iostream>

#include <algorithm>

CommandParser::CommandParser() 
{
    this->_commands["PASS"] = new CmdPass();
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
            params.back() + " " + line.substr(i);
            break;
        }
    }
    return (params);
}

void CommandParser::_process(FtIRCd &serverInstance, Client &client, const std::string &line)
{
    std::vector<std::string> tokens;
    std::string cmd;

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
            client._send(": " + serverInstance._getServername() + " 421 " + client._getNick() + " " + cmd + " :Unknown commmand");
        return ;
    }

    ACommand *command = it->second;

    // ### TODO: command分 +1している　改善しよう
    std::vector<std::string> params = this->_split(line, command->_getMaxParams() + 1);
    params.erase(params.begin());

    // 登録前に使えない
    if (!command->_getWorksBeforeReg() && !client._isRegistered())
    {
        client._send(": " + serverInstance._getServername() + " 451 " + client._getNick() + " :You have not registered");
        return;
    }

    // min paramチェック
    if (params.size() < command->_getMinParams())
    {
        client._send(": " + serverInstance._getServername() + " 461 " + client._getNick() + " " + cmd + " :Not enough parameters.");
        return ;
    }
    
    command->_execute(serverInstance, client, params);
}