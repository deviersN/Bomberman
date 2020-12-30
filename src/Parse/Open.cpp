//
// EPITECH PROJECT, 2018
// Open
// File description:
// cpp
//

#include <string>
#include "Open.hpp"

// Public
Open::Open(const std::string &fileName, const std::string &path) : _fileName(path + fileName)
{
	init();
}

Open::~Open(void)
{
	_file.close();
	_content.clear();
}

std::vector<std::string>	Open::getContent(void) const
{
	return _content;
}

// Private
void	Open::init(void)
{
	std::string	line;

	if (!_fileName.empty()) {
		_file.open(_fileName);
		if (!_file.is_open())
			std::cout << "Error : File \""
				  << _fileName << "\" cannot be open !"
				  << std::endl;
		while (std::getline(_file, line))
			_content.push_back(line);
	}
	else
		std::cout << "Error : File name must be non-NULL" << std::endl;
}
