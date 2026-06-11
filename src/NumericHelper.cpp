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

Numerics::NoSuchChannel::NoSuchChannel(const std::string &cname)
    : NumericReply(ERR_NOSUCHCHANNEL, cname + " :No such channel")
{}

Numerics::NoSuchNick::NoSuchNick(const std::string &nick)
    : NumericReply(ERR_NOSUCHNICK, nick + " :No such nick")
{}

Numerics::NotOnChannel::NotOnChannel(const std::string &cname)
    : NumericReply(ERR_NOTONCHANNEL, cname + " :You're not on that channel")
{}

Numerics::ChanOpPrivsNeeded::ChanOpPrivsNeeded(const std::string &cname)
    : NumericReply(ERR_CHANOPRIVSNEEDED, cname + " :You're not channel operator")
{}

Numerics::UserNotInChannel::UserNotInChannel(const std::string &nick, const std::string &cname)
    : NumericReply(ERR_USERNOTINCHANNEL, nick + " " + cname + " :They aren't on that channel")
{}

Numerics::NeedMoreParams::NeedMoreParams(const std::string &cmd)
    : NumericReply(ERR_NEEDMOREPARAMS,  cmd + " :Not enough parameters.")
{}