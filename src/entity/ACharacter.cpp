//
// EPITECH PROJECT, 2018
// indie
// File description:
// Acharacter
//

#include <cmath>
#include "ACharacter.hpp"
#include "Mixer.hpp"

ACharacter::ACharacter(void)
{
	_data.canWallPass = false;
	_data.bombMax = 1;
	_data.power = 1.0;
	_data.speed = 1.0;
}

ACharacter::~ACharacter(void)
{
}

// Getters
bool		ACharacter::isAlive(void) const noexcept
{
	return _alive;
}

int		ACharacter::getBombMax(void) const noexcept
{
	return _data.bombMax;
}

bool		ACharacter::isInBomb(void) const noexcept
{
	return _inBomb;
}

float		ACharacter::getPower(void) const noexcept
{
	return _data.power;
}

bool		ACharacter::canWallPass(void) const noexcept
{
	return _data.canWallPass;
}

Pos_t		ACharacter::getPosition(void) const
{
	return _data.pos;
}

EntData_t	ACharacter::getEntData(void) const
{
	return _data;
}

float		ACharacter::getSpeed(void) const noexcept
{
	return _data.speed;
}

// Setters
void		ACharacter::leaveBomb(void) noexcept
{
	_inBomb = false;
}

void		ACharacter::setAlive(const bool &alive)
{
	_alive = alive;
}

void		ACharacter::setPosition(const Pos_t &pos)
{
	_data.pos = pos;
}

void		ACharacter::setBombMax(const int &nbBomb)
{
	_data.bombMax = nbBomb;
}

void		ACharacter::setPower(const float &power)
{
	_data.power = power;
}

void		ACharacter::setWallPass(const bool &canWallPass)
{
	_data.canWallPass = canWallPass;
}

void		ACharacter::setSpeed(const float &speed)
{
	_data.speed = speed;
}

void		ACharacter::setEntData(const EntData_t &data)
{
	_data = data;
}

// Methods
void		ACharacter::kill(void) noexcept
{
	if (_alive)
		Mixer::mixer.playEffectDie();
	_alive = false;
}

bool		ACharacter::matchPosition(int x, int y) const noexcept
{
	Pos_t	pos = _data.pos;
	int	posX = static_cast<int>(std::round(pos.x));
	int	posY = static_cast<int>(std::round(pos.y));

	if (x == posX && y == posY)
		return true;
	if (static_cast<float>(posX) == std::round(pos.x)) {
		if (pos.y < std::round(pos.y))
			posY = static_cast<int>(std::floor(pos.y));
		else
			posY = static_cast<int>(std::ceil(pos.y));
	} else {
		if (pos.x < std::round(pos.x))
			posX = static_cast<int>(std::floor(pos.x));
		else
			posX = static_cast<int>(std::ceil(pos.x));
	}
	return (x == posX && y == posY);
}

void		ACharacter::reducePlacedBomb(void) noexcept
{
	--_placedBomb;
	if (_placedBomb < 0)
		_placedBomb = 0;
}

// Boosts
void	ACharacter::bombUp(void) noexcept
{
	_data.bombMax += BOOST_BOMBUP_VALUE;
	if (_data.bombMax >= BOOST_BOMBUP_MAX)
		_data.bombMax = BOOST_BOMBUP_MAX;
}

void	ACharacter::empower(void) noexcept
{
	_data.power += BOOST_FIRE_VALUE;
	if (_data.power >= BOOST_FIRE_MAX)
		_data.power = BOOST_FIRE_MAX;
}

void	ACharacter::wallPass(void) noexcept
{
	_data.canWallPass = true;
}

void	ACharacter::accelerate(void) noexcept
{
	_data.speed += BOOST_SPEED_VALUE;
	if (_data.speed >= BOOST_SPEED_MAX)
		_data.speed = BOOST_SPEED_MAX;
}

// Protected methods
void		ACharacter::moving(MapHandler &map, int direction)
{
	map.moveEntity(*this, direction);
}

void	ACharacter::placeBomb(MapHandler &map)
{
	if (_placedBomb >= _data.bombMax)
		return;
	if (map.addBomb(_data.pos, _data.power, this)) {
		Mixer::mixer.playEffectDropBomb();
		_inBomb = true;
		++_placedBomb;
	}
}
