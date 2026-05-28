/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdQuit.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-28 03:03:13 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-28 03:03:13 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDQUIT_HPP
# define CMDQUIT_HPP

#include "ACommand.hpp"

class CmdQuit: public ACommand
{
    public:
        CmdQuit();
        ~CmdQuit();

        void    _execute(FtIRCd &serverInstance, Client &client, std::vector<std::string> &params);
};

#endif