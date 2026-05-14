/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketEngine.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-14 01:02:29 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-14 01:02:29 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SocketEngine.hpp"
#include <unistd.h>
#include <stdexcept>
#include <cstring>

SocketEngine::SocketEngine()
{
    this->_epfd = epoll_create1(0);
    if (this->_epfd < 0)
        throw std::runtime_error("epoll_create() failed: " + std::string(std::strerror(errno)));
}

SocketEngine::~SocketEngine()
{
    if (this->_epfd >= 0)
        close(this->_epfd);
}

void SocketEngine::addFd(int fd, uint32_t events)
{
    struct epoll_event ev;

    ev.events = events;
    ev.data.fd = fd;
    epoll_ctl(this->_epfd, EPOLL_CTL_ADD, fd, &ev); // ### TODO: エラー処理
    this->_fds.insert(fd);
}

void SocketEngine::delFd(int fd)
{
    if (this->_fds.find(fd) == this->_fds.end())
        return ;
    epoll_ctl(this->_epfd, EPOLL_CTL_DEL, fd, NULL); // ### TODO: エラー処理
    this->_fds.erase(fd);
}

std::vector<int> SocketEngine::dispatch(int timeout_ms)
{
    std::vector<int> ready;
    int nfds;

    nfds = epoll_wait(this->_epfd, this->_events, 64, timeout_ms); // ### TODO: 64が適切か考える
    if (nfds < 0)
    {
        // シグナル割り込みのケース
        // if (errno == EINTR)
        //     return (ready);
        throw std::runtime_error("epoll_wait() failed: " + std::string(std::strerror(errno)));
    }

    for (int i = 0; i < nfds; ++i)
    {
        if (this->_events[i].events & (EPOLLIN | EPOLLHUP | EPOLLERR))
            ready.push_back(this->_events[i].data.fd);
    }
    return (ready);
}