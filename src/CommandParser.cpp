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
#include "ft_ircd.hpp"
#include "Client.hpp"
#include <iostream>

#include <algorithm>

CommandParser::CommandParser() {}

CommandParser::~CommandParser() {}

void CommandParser::_cmdPass(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params)
{
    if (params.size() < 2)
    {
        clients.send(":" + this->serverInstance._getServername() + "461 " + client.getNick() + "PASS :Not enough parameters.");
        return ;
    }
}

std::vector<std::string> CommandParser::_split(const std::string &line)
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
    std::vector<std::string> params;
    std::string cmd;

    if (line.empty())
        return ;
    
    params = this->_split(line);
    if (params.empty())
        return ;

    cmd = params[0];
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);

    // ### TODO: 定数化すべきかな
    if (cmd == "PASS") // パラメータが多い場合結合する
        this->_cmdPass(serverInstance, client, this->_split(line, 2));
    else if (cmd == "NICK") // パラメータが多い場合無視する
        this->_cmdNick(serverInstance, client, this->_split(line));
    else if (cmd == "USER") // パラメータが多い場合結合する
        this->_cmdUser(serverInstance, client, this->_split(line, 5));
    else
        std::cout << cmd <<  " :Unknown command" << std::endl;
}