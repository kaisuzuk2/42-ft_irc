/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdPass.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-16 22:59:01 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-16 22:59:01 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDPASS_HPP
# define CMDPASS_HPP

#include "commands/ACommand.hpp"

class CmdPass: public ACommand
{
    public:
        CmdPass();
        ~CmdPass();

        void _execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params);
};

#endif