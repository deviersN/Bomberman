//
// EPITECH PROJECT, 2018
// indie
// File description:
// boost fireup
//

#include "BoostFireUp.hpp"

BoostFireUp::BoostFireUp(void)
{
	_type = POWER_FIREUP;
}

BoostFireUp::~BoostFireUp(void)
{
}

// Methods
void	BoostFireUp::applyBoost(ACharacter &target)
{
	target.empower();
}