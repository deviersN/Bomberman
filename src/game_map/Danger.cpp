//
// EPITECH PROJECT, 2018
// Indie
// File description:
// DangerousMap
//

#include "Map.hpp"
#include "Danger.hpp"

Danger::Danger(std::size_t height, std::size_t width) : Map::Map()
{
	_height = height;
	_width = width;
	_map = nullptr;
	create(_width, _height);
	std::cout << _height << " -- " << _width << " : map size"
	<< std::endl;
}

Danger::~Danger()
{
	if (_map != nullptr) {
		this->destroy();
	}
}

/*
** compute the position of every bomb currently placed
** to deduce the dangerous areas.
** (Note : generalMap = the map with walls and obstacles).
*/
void			Danger::dropBombs(
	std::vector<Bomb*> explosiveBelt, Map *generalMap)
{
	std::size_t	i = 0;

	create(_width, _height);
	while (i < explosiveBelt.size()) {
		evaluateDanger(explosiveBelt[i], generalMap);
		i += 1;
	}
}

/*
** Called by dropBomb
** deduce a bomb's dangerous area on the map
*/
void    Danger::evaluateDanger(Bomb *bomb, Map *casualMap)
{
	set(bomb->getPosition().x, bomb->getPosition().y, 1);
	for (std::size_t i = 1;
		i < bomb->getPower() && bomb->getPosition().x + i < _width &&
		casualMap->get(bomb->getPosition().x + i, bomb->getPosition().y)
		== SAFE; i += 1) {
		_map[(int)bomb->getPosition().x + i][(int)bomb->getPosition().y]
		= RISKNBORDER;
	}
	for (std::size_t i = 1;
		i < bomb->getPower() && bomb->getPosition().x - i >= 0 &&
		casualMap->get(bomb->getPosition().x - i, bomb->getPosition().y)
		== SAFE; i += 1) {
		_map[(int)bomb->getPosition().x - i][(int)bomb->getPosition().y]
		= RISKNBORDER;
	}
	for (std::size_t i = 1;
		i < bomb->getPower() && bomb->getPosition().y + i < _height &&
		casualMap->get(bomb->getPosition().x, bomb->getPosition().y + i)
		== SAFE; i += 1) {
		_map[(int)bomb->getPosition().x][(int)bomb->getPosition().y + i]
		= RISKNBORDER;
	}
	for (std::size_t i = 1;
		i < bomb->getPower() && bomb->getPosition().y - i >= 0 &&
		casualMap->get(bomb->getPosition().x, bomb->getPosition().y - i)
		== SAFE; i += 1) {
		_map[(int)bomb->getPosition().x][(int)bomb->getPosition().y - i]
		= RISKNBORDER;
	}
}

int	**Danger::getDangerMap()
{
	return this->_map;
}
