/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-16 23:15:30 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-16 23:15:30 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACOMMAND_HPP
# define ACOMMAND_HPP

#include <string>
#include <vector>

class FtIRCd;
class Client;

class ACommand  
{
    private:
        const std::string   _name;
        const unsigned int _min_params;
        const unsigned int _max_params;
        bool               _works_before_reg;
    public:

        ACommand(const std::string &name, const unsigned int min_params, const unsigned int max_params, const bool works_before_reg);
        virtual ~ACommand();

        virtual void        _execute(FtIRCd &serverInstance, Client &client, const std::vector<std::string> &params) = 0;

        const std::string   &_getName() const;
        unsigned int        _getMinParams() const;
        unsigned int        _getMaxParams() const;
        bool                _getWorksBeforeReg() const;

    protected:
        void                _setWorksBeforeReg(bool);
};

#endif