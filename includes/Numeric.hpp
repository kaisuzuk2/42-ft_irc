/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Numeric.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-21 01:45:23 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-21 01:45:23 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMERIC_HPP
# define NUMERIC_HPP

enum Numeric 
{
    RPL_WELCOME             = 1, 
    // RPL_YOURHOST            = 2,
    // RPL_CREATED             = 3,
    // RPL_MYINFO              = 4,

    RPL_INVITING            = 341,
    RPL_NAMREPLY            = 353,
    RPL_ENDOFNAMES          = 366,

    ERR_NOSUCHNICK          = 401,
    ERR_NOSUCHCHANNEL       = 403, // ### TODO: 複数で使用　エラーメッセージ統一しないといけない
    ERR_CANNOTSENDTOCHAN    = 404,
    ERR_TOOMANYCHANNELS     = 405,
    ERR_NORECIPIENT         = 411,
    ERR_NOTEXTTOSEND        = 412,
    ERR_UNKNOWNCOMMAND      = 421,
    ERR_NONICKNAMEGIVEN     = 431,
    ERR_ERRONEUSNICKNAME    = 432,
    ERR_NICKNAMEINUSE       = 433,
    ERR_USERNOTINCHANNEL    = 441, 
    ERR_NOTONCHANNEL        = 442,
    ERR_USERONCHANNEL       = 443,
    ERR_NOTREGISTERED       = 451,
    ERR_NEEDMOREPARAMS      = 461,
    ERR_ALREADYREGISTERED   = 462,
    ERR_PASSWDMISMATCH      = 464,
    ERR_BADCHANNELKEY       = 475,
    ERR_BADCHANMASK         = 476,
    ERR_CHANOPRIVSNEEDED    = 482,

    // from irc-hybrid(insprcd)
    RPL_INVITELIST          = 336,
    RPL_ENDOFINVITELIST     = 337,

    // from ircu (inspircd)
    ERR_INVALIDUSERNAME     = 468,
};

#endif