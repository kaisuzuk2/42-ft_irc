/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketEngine.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-14 00:58:07 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-14 00:58:07 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKETENGINE_HPP
# define SOCKETENGINE_HPP

#include <set>
#include <vector>
#include <sys/epoll.h>

#include <cerrno>

class SocketEngine 
{
    private:
        int                 _epfd;
        struct epoll_event  _events[64]; // ### TODO: 数が適切かな
        std::set<int>       _fds;
    public:
        SocketEngine();
        ~SocketEngine();

        void                addFd(int fd, uint32_t events);
        void                delFd(int fd);
        std::vector<int>    dispatch(int timeout_ms);
};

#endif