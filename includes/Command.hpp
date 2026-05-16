/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-16 22:24:25 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-16 22:24:25 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP

#include <string>
#include <vector>

class FtIRCd;
class Client;

class Command  
{
    private:
        const std::string   _name;
        const unsigned int _min_params;
        const unsigned int _max_params;
        bool                works_before_reg;
    public:

        Command(const std::string &name, const unsigned int min_params, const unsigned int max_params);
        virtual ~Command();

        virtual void        execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params) = 0;

        const std:;string   &_getName() const;
        unsigned int        _getMinParams() const;
        unsigned int        _getMaxParams() const;
        bool                _getworkBeforeReg() const;
        void                _setWorkBeforeReg(bool);
};

#endif