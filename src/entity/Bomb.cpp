//
// EPITECH PROJECT, 2018
// indie
// File description:
// bomb
//

#include <iostream>
#include "Bomb.hpp"

Bomb::Bomb(const Pos_t &pos, int power, ACharacter *owner)
: _power(power), _position(pos), _owner(owner),
_start(std::chrono::system_clock::now())
{
}

Bomb::~Bomb()
{
}

// Methods
bool	Bomb::clock(void) noexcept
{
	auto	now = std::chrono::system_clock::now();
	std::chrono::duration<double>	diff = now - _start;

	if (diff.count() >= BOMB_COUNTDOWN || _prematured)
		return true;
	return false;
}

void	Bomb::premature(void) noexcept
{
	_prematured = true;
}

void	Bomb::reduceOwner(void) noexcept
{
	if (_owner != nullptr)
		_owner->reducePlacedBomb();
}

// Getters
int	Bomb::getPower(void) const noexcept
{
	return _power;
}

Pos_t	Bomb::getPosition(void) const
{
	return _position;
}

// Setters
void	Bomb::setPosition(const Pos_t &pos)
{
	_position = pos;
}