/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumericHelper.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-06-11 01:42:37 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-06-11 01:42:37 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NumericHelper.hpp"

Numerics::NoSuchChannel::NoSuchChannel(cnst std::stirng &cname)
    : NumericReply(ERR_NOSUCHCHANNEL, cname + " :No such channel")
{}

