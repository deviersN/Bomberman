//
// EPITECH PROJECT, 2018
// indie
// File description:
// boost speedup
//

#include "BoostSpeedUp.hpp"

BoostSpeedUp::BoostSpeedUp(void)
{
	_type = POWER_SPEEDUP;
}

BoostSpeedUp::~BoostSpeedUp(void)
{
}

// Methods
void	BoostSpeedUp::applyBoost(ACharacter &target)
{
	target.accelerate();
}