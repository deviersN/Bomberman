//
// EPITECH PROJECT, 2018
// indie
// File description:
// Aboost
//

#include "ABoost.hpp"
#include "BoostBombUp.hpp"
#include "BoostFireUp.hpp"
#include "BoostSpeedUp.hpp"
#include "BoostWallPass.hpp"

ABoost::ABoost(void)
{
}

ABoost::~ABoost(void)
{
}

// Getters
PowerUp_t	ABoost::getType(void) const
{
	return _type;
}

Pos_t		ABoost::getPosition(void) const
{
	return _pos;
}

const Coords	ABoost::getCoords(void) const
{
	Coords	ret;

	ret.x = static_cast<int>(_pos.x);
	ret.y = static_cast<int>(_pos.y);
	return ret;
}

// Setters
void	ABoost::setPosition(const Pos_t &pos)
{
	_pos = pos;
}

// Static methods
ABoost	*ABoost::dropBoost(void)
{
	int	randValue = rand() % POWER__MAX;

	switch (randValue) {
		case POWER_BOMBUP: return new BoostBombUp;
		case POWER_FIREUP: return new BoostFireUp;
		case POWER_SPEEDUP: return new BoostSpeedUp;
		case POWER_WALLPASS: return new BoostWallPass;
	}
	return nullptr;
}