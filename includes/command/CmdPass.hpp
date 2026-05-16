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

#include "Comamnd.hpp"

class CmdPass: public Command
{
    public:
        CmdPass();
        ~CmdPass();

        void execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> params);
};

#endif