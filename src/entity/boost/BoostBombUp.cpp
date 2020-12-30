//
// EPITECH PROJECT, 2018
// indie
// File description:
// boost bombup
//

#include "BoostBombUp.hpp"

BoostBombUp::BoostBombUp(void)
{
	_type = POWER_BOMBUP;
}

BoostBombUp::~BoostBombUp(void)
{
}

// Methods
void	BoostBombUp::applyBoost(ACharacter &target)
{
	target.bombUp();
}