/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdUser.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-21 23:15:49 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-21 23:15:49 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDUSER_HPP
# define CMDUSER_HPP

class CmdUser: public ACommand
{
    public:
        CmdUser();
        ~CmdUser();

        void _execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params);
};

#endif