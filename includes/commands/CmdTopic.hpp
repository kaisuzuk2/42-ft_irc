/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdTopic.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 01:12:06 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/06/24 09:41:56 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDTOPIC_HPP
# define CMDTOPIC_HPP

#include "ACommand.hpp"
#include "Channel.hpp"
#include "ft_ircd.hpp"

class CmdTopic: public ACommand
{
    public:
        CmdTopic();
        ~CmdTopic();

        void    _execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params);
};

#endif
