//
// EPITECH PROJECT, 2018
// indie
// File description:
// boost wallpass
//

#include "BoostWallPass.hpp"

BoostWallPass::BoostWallPass(void)
{
	_type = POWER_WALLPASS;
}

BoostWallPass::~BoostWallPass(void)
{
}

// Methods
void	BoostWallPass::applyBoost(ACharacter &target)
{
	target.wallPass();
}