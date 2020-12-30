//
// EPITECH PROJECT, 2018
// indie
// File description:
// player
//

#include <iostream>
#include "Player.hpp"

Action_t Player::g_actions[2] = {ACTION_MOVE_DOWN, ACTION_NONE};;

Player::Player(int id)
: _id(id)
{
}

Player::~Player()
{
}

// Getters
bool	Player::isMoving(void) const noexcept
{
	if (!_alive || _id >= 2)
		return false;
	if (g_actions[_id] != ACTION_NONE
	&& g_actions[_id] != ACTION_PLACE_BOMB)
		return true;
	return false;
}

bool	Player::isPlayer(void) const noexcept
{
	return true;
}

// Methods
void	Player::say(void) const noexcept
{
	std::cout << "--- Player[" << _id << "] ---" << std::endl;
	std::cout << "[> pos:\t\t" << _data.pos.x << " ; "
	<< _data.pos.y << std::endl << "[> alive:\t";
	if (_alive)
		std::cout << "YES" << std::endl;
	else
		std::cout << "NO" << std::endl;
}

void	Player::doAction(MapHandler &map)
{
	Action_t	myAction = ACTION_NONE;

	if (!_alive)
		return;
	if (_id < 2)
		myAction = g_actions[_id];
	if (myAction == ACTION_PLACE_BOMB) {
		this->placeBomb(map);
	} else if (myAction != ACTION_NONE) {
		this->moving(map, (int) myAction);
		_data.pos.direction = myAction;
	}
}
