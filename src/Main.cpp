//
// EPITECH PROJECT, 2018
// indie
// File description:
// main
//

// MAIN TEST GUI

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Gui.hpp"

#include "Exception.hpp"

int	main(int arc, const char *const *argv)
{
	Gui	gui(argv[0]);
	int	ret = 0;

	std::srand(std::time(nullptr));
	try {
		gui.displayMenu();
	} catch (Exception e) {
		std::cerr << "Fatal exception: " << e.what() << std::endl;
		ret = 84;
	}
	gui.destroyAll();
	return ret;
}