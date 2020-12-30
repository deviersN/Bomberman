//
// EPITECH PROJECT, 2018
// indie
// File description:
// flame
//

#include "Flame.hpp"

Flame::Flame(const Pos_t &pos)
: _position(pos), _start(std::chrono::system_clock::now())
{
}

Flame::~Flame()
{
}

// Methods
bool	Flame::clock(void) noexcept
{
	auto	now = std::chrono::system_clock::now();
	std::chrono::duration<double>	diff = now - _start;

	if (diff.count() >= FLAME_COUNTDOWN)
		return true;
	return false;
}

// Getters
Pos_t	Flame::getPosition(void) const
{
	return _position;
}

// Setters
void	Flame::setPosition(const Pos_t &pos)
{
	_position = pos;
}