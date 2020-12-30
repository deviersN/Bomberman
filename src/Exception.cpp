//
// EPITECH PROJECT, 2018
// indie
// File description:
// exception
//

#include "Exception.hpp"

Exception::Exception(const std::string &error)
: _message(error)
{
}

Exception::~Exception()
{
}

// Methods
const char	*Exception::what(void) const noexcept
{
	return _message.c_str();
}