/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdPart.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-28 00:33:47 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-28 00:33:47 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "comamnds/CmdPart.hpp"

/*
RFC 1459
パラメータ:  <channel>{,<channel>}

RFC 2812
パラメーター: <channel> *( "," <channel> ) [ <Part Message> ]
*/

CmdPart::CmdPart() 
    : ACommand("PART", 1, 2, false)
{}

CmdPart::~CmdPart() {}

