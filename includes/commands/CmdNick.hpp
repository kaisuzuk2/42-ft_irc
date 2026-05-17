/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdNick.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-17 00:32:42 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-17 00:32:42 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDNICK_HPP
# define CMDNICK_HPP

#include "ACommand.hpp"

class CmdNick: public ACommand
{
    public:
        CmdNick();
        ~CmdNick();

        void _execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params);
};

#endif