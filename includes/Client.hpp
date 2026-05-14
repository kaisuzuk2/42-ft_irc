/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-14 01:37:41 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-14 01:37:41 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <netinet/in.h>

class Client
{
    private:
        int                 _fd;
        struct sockaddr_in  _addr;
        std::string         _nick;
        std::string         _hostname;
    public:
        Client(int fd, const struct sockaddr_in &addr);
        ~Client();

        int                 getFd() const;
        const std::string&  getNick() const;
};