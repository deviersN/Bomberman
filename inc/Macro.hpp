//
// EPITECH PROJECT, 2018
// indie
// File description:
// macro
//

#ifndef MACRO_HPP_
	#define MACRO_HPP_

	///// Map / Wall /////
	#ifndef MAP_TYPES
		#define MAP_TYPES

		#define MAP_TYPE_FLAME	-1
		#define MAP_TYPE_EMPTY	0
		#define MAP_TYPE_WALL	1
		#define MAP_TYPE_BLOC	2
		#define MAP_TYPE_BOMB	3
		#define MAP_TYPE_BOOST	-2
	#endif /* !MAP_TYPES */
	#ifndef MAP_WIDTH_POS_SYMBOL
		#define MAP_WIDTH_POS_SYMBOL	-1
	#endif /* !MAP_WIDTH_POS_SYMBOL */
	#ifndef MAP_HEIGTH_POS_SYMBOL
		#define MAP_HEIGTH_POS_SYMBOL	-2
	#endif /* !MAP_HEIGTH_POS_SYMBOL */

	///// BOOSTS /////
	#ifndef BOOST_VALUES
		#define BOOST_VALUES

		#define BOOST_BOMBUP_VALUE	1
		#define BOOST_FIRE_VALUE	1.0
		#define BOOST_SPEED_VALUE	0.1

		#define BOOST_BOMBUP_MAX	10
		#define BOOST_FIRE_MAX		30
		#define BOOST_SPEED_MAX		2.1

		#define BOOST_DROP_CHANCE	40
	#endif /* !BOOST_VALUES */

	///// Entities / Players / Npc /////
	#ifndef ENT_LARG_ERR
		#define ENT_LARG_ERR	0.251
	#endif /* !ENT_LARG_ERR */
	#ifndef ENT_SPEED
		#define ENT_SPEED	0.08 // Must be calculated
	#endif /* !ENT_SPEED */
	#ifndef ENT_AMOUNT
		#define ENT_AMOUNT	4
	#endif /* !ENT_AMOUNT */

	#ifndef DIRECTIONNAL
		#define DIRECTIONNAL

		#define DIREC_LEFT		-2
		#define DIREC_UP		-1
		#define DIREC_DOWN		1
		#define DIREC_RIGHT		2

		#define DIREC_GET_MOVE_X(direction)	direction / 2;
		#define DIREC_GET_MOVE_Y(direction)	direction % 2;
	#endif /* !DIRECTIONNAL */


	///// Bomb / Explosion / Flame /////
	#ifndef BOMB_COUNTDOWN
		#define BOMB_COUNTDOWN	2
	#endif /* !BOMB_COUNTDOWN */
	#ifndef FLAME_COUTDOWN
		#define FLAME_COUNTDOWN	0.5
	#endif /* !FLAME_COUTDOWN */

#endif /* !MACRO_HPP_ */
