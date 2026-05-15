/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ircd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-15 00:10:38 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-15 00:10:38 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRCD_HPP
# define FT_IRCD_HPP

#include <string>

#include "SocketEngine.hpp"
#include "ClientManager.hpp"

class FtIRCd 
{
    private:
        int             _port;
        std::string     _password;
        int             _serverFd;
        SocketEngine    _socketEngine;
        ClientManager   _clients;

    public:
        FtIRCd(int argc, char **argv);
        ~FtIRCd();

        void             _run();

    private:
        void            _acceptClient();
        void            _handleClient(int fd);
        void            _disconnectClient(int fd);
};

#endif