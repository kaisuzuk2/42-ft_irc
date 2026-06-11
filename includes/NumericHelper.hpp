/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumericHelper.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-06-11 01:40:51 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-06-11 01:40:51 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMERICHELPER_HPP
# define NUMERICHELPER_HPP

#include "NumericReply.hpp"
#include "Numeric.hpp"

namespace Numerics
{
    class NoSuchChannel;
    class NoSuchNick;
    class NotOnChannel;
    class ChanOpPrivsNeeded;
}

class Numerics::NoSuchChannel: public NumericReply
{
    public:
        NoSuchChannel(const std::string &cname);
};

class Numerics::NoSuchNick: public NumericReply
{
    public:
        NoSuchNick(const std::string &nick);
};

class Numerics::NotOnChannel: public NumericReply
{
    public:
        NotOnChannel(const std::string &cname);
};

class Numerics::ChanOpPrivsNeeded: public NumericReply
{
    public:
        ChanOpPrivsNeeded(const std::string &cname);
};

#endif