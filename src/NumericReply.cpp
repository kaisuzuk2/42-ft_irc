/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumericReply.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 01:37:14 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026/06/24 09:43:02 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NumericReply.hpp"

NumericReply::NumericReply(unsigned int num, const std::string &msg)
    : _num(num)
    , _msg(msg)
{}

unsigned int NumericReply::_getNum() const
{
    return (this->_num);
}

const std::string &NumericReply::_getMsg() const
{
    return (this->_msg);
}
