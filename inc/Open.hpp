//
// EPITECH PROJECT, 2018
// open
// File description:
// open file and extract content
//

#ifndef OPEN_HPP_
	#define OPEN_HPP_

	#include <vector>
	#include <iostream>
	#include <fstream>
	#include <stdbool.h>

	class Open {
	public:
		Open(const std::string &fileName, const std::string &path = "");
		~Open(void);
		std::vector<std::string>	getContent(void) const;
		
	private:
		void				init(void);
		std::ifstream			_file;
		std::vector<std::string>	_content;
		std::string			_fileName;
	};

#endif /* !OPEN_HPP_ */
