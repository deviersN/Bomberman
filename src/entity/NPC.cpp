//
// EPITECH PROJECT, 2018
// Indie
// File description:
// NPC
//

#include <iostream>
#include "NPC.hpp"
#include "Exception.hpp"

Npc::Npc(int id) : _id(id), _riskzone(nullptr)
{
	_alive = true;
}

Npc::~Npc(void)
{
}

void	Npc::say(void) const noexcept
{
	std::cout << "--- Npc[" << _id << "] ---" << std::endl;
	std::cout << "[> pos:\t\t" << _data.pos.x << " ; "
	<< _data.pos.y << std::endl << "[> alive:\t";
	if (_alive) {
		std::cout << "YES" << std::endl;
	} else {
		std::cout << "NO" << std::endl;
	}
}

bool		Npc::isMoving(void) const noexcept
{
	return true;
}

void			Npc::doAction(MapHandler &map)
{
	std::list<Bomb*>	bombList = map.getBombList();
	std::vector<Bomb*>	bombVector;
	Map			*casualMap = map.getMap();
	Action_t		myAction;

	for (auto it = bombList.begin(); it != bombList.end(); it++)
		bombVector.push_back(*it);
	if (_riskzone == nullptr)
		_riskzone = new Danger(casualMap->getW(), casualMap->getH());
	_riskzone->dropBombs(bombVector, map.getMap());
	myAction = behaviour(casualMap);
	if (myAction == ACTION_PLACE_BOMB) {
		this->placeBomb(map);
	} else if (myAction != ACTION_NONE) {
		map.moveEntity(*this, (int)myAction);
	}
}

bool		Npc::isPlayer(void) const noexcept
{
	return false;
}

/*
** behaviour()
** selects the short term objective of the NPC between :
** -staying safe if surrounded by dangerous places
** -escaping towards the nearest safe place if threatened
** -hunting for blocks to destroy or players to annihilate
*/
Action_t		Npc::behaviour(Map *map)
{
        static Action_t myAction = ACTION_NONE;
	static size_t	count = 30;

	if (_alive == false)
		return ACTION_NONE;
	count -= 1;
	if (count == 0) {
		count = 50;
		myAction = newDirection(map);
	}
	if (myAction == ACTION_PLACE_BOMB)
		count = 1;
	return myAction;
}

Action_t	Npc::newDirection(Map *map)
{
	static Action_t lastAction = ACTION_NONE;
	Action_t myAction = ACTION_NONE;

	if (_riskzone->get(_data.pos.x, _data.pos.y) != 0) {
		myAction = turnOver(lastAction);
	} else if (stuckToBloc(map)) {
		myAction = ACTION_PLACE_BOMB;
	} else {
		lastAction = findAWay(map, lastAction);
		return lastAction;
	}
	return myAction;
}

Action_t	Npc::turnOver(Action_t dir)
{
        switch((int) dir)
	{
	case (ACTION_MOVE_LEFT):
		return ACTION_MOVE_RIGHT;
	case (ACTION_MOVE_UP):
		return ACTION_MOVE_DOWN;
	case (ACTION_MOVE_DOWN):
		return ACTION_MOVE_UP;
	case (ACTION_MOVE_RIGHT):
		return ACTION_MOVE_LEFT;
	default:
		return ACTION_NONE;
	}
}

bool	Npc::stuckToBloc(Map *map)
{
	std::size_t x = _data.pos.x;
	std::size_t y = _data.pos.y;
	std::size_t xMax = map->getW();
	std::size_t yMax = map->getH();

        
	if ((x != xMax && map->getNE(x + 1, y) == MAP_TYPE_BLOC)
	    || (x != 0 && map->getNE(x - 1, y) == MAP_TYPE_BLOC)
	    || (y != yMax && map->getNE(x , y + 1) == MAP_TYPE_BLOC)
	    || (y != 0 && map->getNE(x , y - 1) == MAP_TYPE_BLOC)) {
		return true;
	}
	return false;
}

Action_t	Npc::findAWay(Map *map, Action_t lastAction)
{
	Action_t	myAction = (Action_t)(rand() % 6 - 2);
	return myAction;
}
