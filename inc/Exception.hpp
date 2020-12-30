//
// EPITECH PROJECT, 2018
// indie
// File description:
// exception
//

#ifndef EXCEPTION_HPP_
	#define EXCEPTION_HPP_

	#include <exception>
	#include <string>

	class Exception : public std::exception {
	public:
		Exception(const std::string &error);
		~Exception();
		// Methods
		const char	*what(void) const noexcept override;
	private:
		std::string	_message;
	};

#endif /* !EXCEPTION_HPP_ */
