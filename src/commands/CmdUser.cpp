/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdUser.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-21 23:18:14 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-21 23:18:14 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdUser.hpp"

/*
RFC 1459
パラメータ:  <username> <hostname> <servername> <realname>

RFC 2812
パラメーター: <user> <mode> <unused> <realname>
※usermodeは今回実装しないため、modeパラメータは無視する

*/

CmdUser::CmdUser()
    : ACommand("USER", 4, 4, true);
{}





