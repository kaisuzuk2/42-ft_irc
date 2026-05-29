/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdMessage.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-29 00:21:29 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-29 00:21:29 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDMESSAGE_HPP
# define CMDMESSAGE_HPP

#include "ACommand.hpp"

class CmdMessage: public ACommand
{
    private:
        bool    _isNotice; // 離席中のユーザーにAWAYをリプライする。今回は実装しないので使わない。

        void    _handleChannelTarget(FtIRCd &serverInstance, Client &client, const std::string &cname, const std::string &msg);
    public:
        CmdMessage(bool isNotice);
        ~CmdMessage();

        void    _execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params);
};

#endif