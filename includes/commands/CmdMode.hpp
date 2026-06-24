/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdMode.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 23:28:25 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/06/24 09:41:32 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDMODE_HPP
# define CMDMODE_HPP

#include "ACommand.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "ft_ircd.hpp"

#include <cerrno>

class CmdMode: public ACommand
{
    public:
        CmdMode();
        ~CmdMode();

        void    _execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params);

    private:
        bool    _applyMode(FtIRCd &serverInstance, Client &client, Channel *ch, char c, bool adding, size_t &paramIdx, const std::vector<std::string> &params, std::string &outParam);
        bool    _applyFlagMode(Channel *ch, char c, bool adding);
        bool    _applyKeyMode(const std::string &servername, Client &client, Channel *ch, bool adding ,size_t &paramIdx, const std::vector<std::string> &params, std::string &outParam);
        bool    _applyLimitMode(const std::string &servername, Client &client, Channel *ch, bool adding, size_t &paramIdx, const std::vector<std::string> &params, std::string &outParam);
        bool    _applyOperMode(FtIRCd &serverInstance, Client &client, Channel *ch, bool adding, size_t &paramIdx, const std::vector<std::string> &params, std::string &outParam);

        void    _appendMode(char c, bool adding, const std::string &outParam, std::string &appliedStr, std::string &appliedParams, char &lastSign);

};

#endif
