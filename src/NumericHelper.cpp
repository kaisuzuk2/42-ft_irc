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
    : NumericReply(ERR_NOSUCHCHANNEL, (cname.empty() ? "*" : cname) + " :No such channel")
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

Numerics::AlreadyRegistered::AlreadyRegistered()
    : NumericReply(ERR_ALREADYREGISTERED, ":Unauthorized command (already registered)")
{}

Numerics::InvalidModeParam::InvalidModeParam(const std::string &cname, char mode, const std::string &modeDesc, const std::string &syntax)
    : NumericReply(ERR_INVALIDMODEPARAM, cname + " " + mode + "* :You must specify a parameter for the " + modeDesc + "mode. Syntax: <" + syntax + ">")
{}