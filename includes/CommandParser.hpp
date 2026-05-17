/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandParser.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-15 03:02:14 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-15 03:02:14 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDPARSER_HPP
# define COMMANDPARSER_HPP

#include <string>
#include <vector>
#include <map>

#include "commands/Command.hpp"

class FtIRCd;
class Client;

class CommandParser
{
    private:
        std::map<std::string, ACommand *>_commands;

    public:
        CommandParser();
        ~CommandParser();
        void                        _process(FtIRCd &serverInstance, Client &client, const std::string &line);
    
    private:
        std::vector<std::string>    _split(const std::string &line, size_t max_params = 0);
};

#endif