/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdNames.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 00:53:36 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/06/24 09:41:39 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDNAMES_HPP
# define CMDNAMES_HPP

#include "ACommand.hpp"

class CmdNames: public ACommand
{
    public:
        CmdNames();
        ~CmdNames();

        void    _execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params);
};

#endif
