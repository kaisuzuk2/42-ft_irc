/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumericReply.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-06-11 01:33:18 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-06-11 01:33:18 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMERICREPLY_HPP
# define NUMERICREPLY_HPP

#include <string>

class NumericReply 
{
    private:
        unsigned int        _num;
        std::string         _msg;

    public:
        NumericReply(unsigned int num, const std::string &msg);

        unsigned int        _getNum() const;
        const std::string   &_getMsg() const;
};

#endif