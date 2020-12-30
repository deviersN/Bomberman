//
// EPITECH PROJECT, 2018
// indie
// File description:
// structure
//

#ifndef STRUCTURE_HPP_
	#define STRUCTURE_HPP_

	#include <cstdint>

	#include "Macro.hpp"

	typedef struct	Pos_s {
		float	x;
		float	y;
		int	direction;
	}		Pos_t;

	typedef struct	EntData_s {
		Pos_t	pos;
		float	power;
		float	speed;
		int	bombMax;
		bool	canWallPass;
	}		EntData_t;

	typedef struct	Coords_s {
		int	x;
		int	y;
	}		Coords;

	typedef enum	PowerUp_e {
		POWER_NONE = -1,
		POWER_FIREUP,
		POWER_SPEEDUP,
		POWER_BOMBUP,
		POWER_WALLPASS,
		POWER__MAX
	}		PowerUp_t;

	typedef enum	Action_e {
		ACTION_MOVE_LEFT = -2,
		ACTION_MOVE_UP,
		ACTION_NONE = 0,
		ACTION_MOVE_DOWN,
		ACTION_MOVE_RIGHT,
		ACTION_PLACE_BOMB
	}		Action_t;

	typedef struct Sound_s {
		int	music;
		int	soundEffect;
	}		Sound_t;

#endif /* !STRUCTURE_HPP_ */
