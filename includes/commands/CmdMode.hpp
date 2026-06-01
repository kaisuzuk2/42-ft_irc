/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdMode.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-31 23:28:25 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-31 23:28:25 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDMODE_HPP
# define CMDMODE_HPP

#include "ACommand.hpp"

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
};

#endif