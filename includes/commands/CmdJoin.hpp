/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdJoin.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-24 01:48:35 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-24 01:48:35 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDJOIN_HPP
# define CMDJOIN_HPP

#include "ACommand.hpp"

class CmdJoin: public ACommand
{
    public:
        CmdJoin();
        ~CmdJoin();

        void    _execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params);
};

#endif