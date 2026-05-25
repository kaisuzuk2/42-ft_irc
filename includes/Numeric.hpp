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

    ERR_UNKNOWNCOMMAND      = 421,
    ERR_NONICKNAMEGIVEN     = 431,
    ERR_ERRONEUSNICKNAME    = 432,
    ERR_NICKNAMEINUSE       = 433,
    ERR_NOTREGISTERED       = 451,
    ERR_NEEDMOREPARAMS      = 461,
    ERR_ALREADYREGISTERED   = 462,
    ERR_PASSWDMISMATCH      = 464,
    ERR_BADCHANMASK         = 476,

    // from ircu (inspircd)
    ERR_INVALIDUSERNAME     = 468,
};

#endif