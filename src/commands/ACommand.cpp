/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-16 23:17:35 by kaisuzuk          #+#    #+#             */
/*   Updated: 2026-05-16 23:17:35 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands/ACommand.hpp"

ACommand::ACommand(const std::string &name, const unsigned int min_params, const unsigned int max_params, const bool works_before_reg)
    : _name(name)
    , _min_params(min_params)
    , _max_params(max_params)
    , _works_before_reg(works_before_reg)
{}

ACommand::~ACommand() {}

const std::string &ACommand::_getName() const
{
    return (this->_name);
}

unsigned int ACommand::_getMinParams() const
{
    return (this->_min_params);
}

unsigned int ACommand::_getMaxParams() const
{
    return (this->_max_params);
}

bool ACommand::_getWorksBeforeReg() const
{
    return (this->_works_before_reg);
}

void ACommand::_setWorksBeforeReg(bool val)
{
    this->_works_before_reg = val;
}