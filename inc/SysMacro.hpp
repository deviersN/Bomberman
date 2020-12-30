/*
** EPITECH PROJECT, 2018
** INDIE
** File description:
**	System relative macros
*/

#ifndef SYS_MACRO_HPP_
	#define SYS_MACRO_HPP_

	#ifdef WIN32
		#define LAST_SLASH "\\"
		#define BASE_ASSETS "\\assets\\"
		#define BACKGROUND_MENU "gui/Background_WIN.png"
		#define TITLE_POS_X 560
		#define TITLE_POS_Y 80
		#define BACKGROUND_MENU_COMMANDS "gui/Background_touche_WIN.png"
		#define TITLE_COMMANDS_POS_X 560
		#define TITLE_COMMANDS_POS_Y 56
		#define BUTTON_REF_SIZE_X 1540
		#define BUTTON_REF_SIZE_Y 500
	#else
		#define LAST_SLASH "/"
		#define BASE_ASSETS "/assets/"
		#define BACKGROUND_MENU "gui/Background.png"
		#define TITLE_POS_X 700
		#define TITLE_POS_Y 100
		#define BACKGROUND_MENU_COMMANDS "gui/Background_touche.png"
		#define TITLE_COMMANDS_POS_X 700
		#define TITLE_COMMANDS_POS_Y 70
		#define BUTTON_REF_SIZE_X 1920
		#define BUTTON_REF_SIZE_Y 639
	#endif

#endif /* !SYS_MACRO_HPP_ */