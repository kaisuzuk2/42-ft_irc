/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdPart.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-28 00:30:29 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-28 00:30:29 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDPART_HPP
# define CMDPART_HPP

#include "ACommand.hpp"

class CmdPart: public ACommand 
{
    public:
        CmdPart();
        ~CmdPart();

        void    _execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params);
    
    private:
        void    _partChannel(FtIRCd &serverInstance, Client &client, const std::string &cname, const std::string &reason);
};

#endif