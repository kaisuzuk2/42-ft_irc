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

class FtIRCd;
class Client;

class CommandParser
{
    public:
        CommandParser();
        ~CommandParser();
        void                        _process(FtIRCd &serverInstance, Client &client, const std::string &line);
    
    private:
        std::vector<std::string>    _split(const std::string &line);

        void                        _cmdPass(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params);
        void                        _cmdNick(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params);
        void                        _cmdUser(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params);
};

#endif