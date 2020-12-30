//
// EPITECH PROJECT, 2018
// indie
// File description:
// maphandler
//

#include <cmath>
#include <cstdlib>
#include <iostream>
#include "NPC.hpp"
#include "Player.hpp"
#include "NPC.hpp"
#include "MapHandler.hpp"
#include "Exception.hpp"
#include "Mixer.hpp"

static const Pos_t defaultPosTable[ENT_AMOUNT] = {
	{0, 0, DIREC_RIGHT},
	{0, 10, DIREC_UP},
	{10, 0, DIREC_DOWN},
	{10, 10, DIREC_LEFT}
};

MapHandler::MapHandler()
{
	initCharacters(2);
}

MapHandler::~MapHandler()
{
	destroyCharacters();
}

// Getters
const CharacterList	&MapHandler::getCharacterList(void) const
{
	return _entlist;
}

Map	*MapHandler::getMap(void)
{
	return &this->_map;
}

PowerUp_t		MapHandler::getBoostTypeAt(int x, int y) const
{
	Coords		coord;

	for (const auto &boost : _boostList) {
		coord = boost->getCoords();
		if (x == coord.x && y == coord.y)
			return boost->getType();
	}
	return POWER_NONE;
}

const ACharacter	&MapHandler::getCharacter(int id) const
{
	if (id < 0 || id >= ENT_AMOUNT)
		throw Exception("Invalid ID");
	return *_entlist[id];
}

int			MapHandler::getCaseValue(int x, int y) const
{
	return _map.get(x, y);
}

int			MapHandler::getWinner(void) const noexcept
{
	return _winner;
}

bool		        MapHandler::noPlayer(void)
{
	bool		ret = false;

	if (!_entlist[0]->isAlive())
		if (!_entlist[1]->isPlayer())
			ret = true;
		else if (!_entlist[1]->isAlive())
			ret = true;
	if (ret) {
		for (int it = 0; it < ENT_AMOUNT; it++)
			if (_entlist[it]->isAlive())
				_winner = it;
	}
	return ret;
}

bool			MapHandler::isOver(void)
{
	int		aliveNb = 0;

	_winner = -1;
	if (noPlayer())
		return true;
	for (int it = 0; it < ENT_AMOUNT; ++it) {
		if (_entlist[it]->isAlive()) {
			++aliveNb;
			_winner = it;
		}
	}
	if (aliveNb <= 1)
		return true;
	return false;
}

BombList		MapHandler::getBombList(void)
{
	return _bomblist;
}

// Setters
void	MapHandler::setMapValue(int x, int y, int value)
{
	_map.set(x, y, value);
}

void	MapHandler::setCharacterList(const CharacterList &list)
{
	for (int it = 0; it < ENT_AMOUNT; ++it) {
		_entlist[it] = list[it];
	}
}

// Methods
void	MapHandler::turn(void)
{
	actionCharacter();
	clockBomb();
}

void	MapHandler::showMap(void) const noexcept
{
	for (int ith = 0; ith < _heigth; ++ith) {
		for (int itw = 0; itw < _width; ++itw)
			std::cout << _map.get(itw, ith) << '\t';
		std::cout << std::endl;
	}
}

bool	MapHandler::addBomb(Pos_t pos, int power, ACharacter *owner)
{
	int value;

	pos.x = std::round(pos.x);
	pos.y = std::round(pos.y);
	value = _map.get(pos);
	if (value != MAP_TYPE_EMPTY)
		return false;
	_bomblist.push_back(new Bomb(pos, power, owner));
	_map.set(pos, MAP_TYPE_BOMB);
	return true;
}

void	MapHandler::generate(int width, int heigth)
{
	_map.create(width, heigth);
	_width = width;
	_heigth = heigth;
	for (int itw = 0; itw < width; ++itw) {
		for (int ith = 0; ith < heigth; ++ith)
			setWall(itw, ith);
	}
	clearSpawn();
}

#ifdef WIN32
void	MapHandler::clockBomb(void)
{
	auto	stopBomb = _bomblist.end();
	auto	stopFlame = _flameList.end();

	for (auto it = _bomblist.begin(); it != stopBomb; ++it) {
		if ((*it)->clock()) {
			createExplosion(**it);
			(*it)->reduceOwner();
			_bomblist.erase(it);
			break;
		}
	}
	for (auto it = _flameList.begin(); it != stopFlame; ++it) {
		if ((*it)->clock()) {
			_map.set((*it)->getPosition(), MAP_TYPE_EMPTY);
			_flameList.erase(it);
			break;
		}
	}
}
#else
void	MapHandler::clockBomb(void)
{
	auto	stopBomb = _bomblist.end();
	auto	stopFlame = _flameList.end();

	for (auto it = _bomblist.begin(); it != stopBomb; ++it) {
		if ((*it)->clock()) {
			createExplosion(**it);
			(*it)->reduceOwner();
			_bomblist.erase(it);
			stopBomb = _bomblist.end();
			it = --_bomblist.begin();
		}
	}
	for (auto it = _flameList.begin(); it != stopFlame; ++it) {
		if ((*it)->clock()) {
			_map.set((*it)->getPosition(), MAP_TYPE_EMPTY);
			_flameList.erase(it);
			it = --_flameList.begin();
			stopFlame = _flameList.end();
		}
	}
}
#endif /* ! WIN32 */

void	MapHandler::playerSay(int id)
{
	if (id >= ENT_AMOUNT)
		throw Exception("Invalid id");
	_entlist[id]->say();
}

void	MapHandler::moveEntity(int id, int direction)
{
	if (id >= ENT_AMOUNT)
		throw Exception("Invalid id");
	this->moveEntity(*_entlist[id], direction);
}

void	MapHandler::moveEntity(ACharacter &ent, int direction)
{
	int	moveX = DIREC_GET_MOVE_X(direction);
	int	moveY = DIREC_GET_MOVE_Y(direction);
	Pos_t	pos = ent.getPosition();
	bool	onY = false;

	if (moveY == 0)
		onY = true;
	pos.x += moveX * ENT_SPEED * ent.getSpeed();
	pos.y += moveY * ENT_SPEED * ent.getSpeed();
	adaptPositions(pos, onY);
	if (!isValidMove(ent, pos, onY))
		embraceWall(pos, onY);
	ent.setPosition(pos);
	applyBoost(ent, pos);
	if (_map.get(pos) == MAP_TYPE_FLAME)
		ent.kill();
}

void	MapHandler::initCharacters(int player_nb)
{
	EntData_t	data;

	data.bombMax = 1;
	data.canWallPass = false;
	data.power = 1;
	data.speed = 1;
	if (player_nb > ENT_AMOUNT || player_nb == 0)
		throw Exception("Invalid amount of players");
	for (auto it = 0; it < ENT_AMOUNT; ++it) {
		if (it < player_nb)
			_entlist[it] = new Player(it);
		else
			_entlist[it] = new Npc(it);
		data.pos = defaultPosTable[it];
		(*_entlist[it]).setEntData(data);
	}
}

void	MapHandler::destroyCharacters(void)
{
	for (auto &ptr : _entlist) {
		if (ptr == nullptr)
			continue;
		delete ptr;
		ptr = nullptr;
	}
}

// Private Methods
Bomb	&MapHandler::findBomb(int x, int y)
{
	Pos_t	position;
	float	cmpX = static_cast<float>(x);
	float	cmpY = static_cast<float>(y);
	auto	stop = _bomblist.end();

	for (auto it = _bomblist.begin(); it != stop; ++it) {
		position = (*it)->getPosition();
		if (std::round(position.x) == cmpX
		&& std::round(position.y) == cmpY)
			return *(*it);
	}
	throw Exception("Can't find bomb with given position");
}

void	MapHandler::applyBoost(ACharacter &ent, const Pos_t &pos)
{
	int		x = static_cast<int>(std::round(pos.x));
	int		y = static_cast<int>(std::round(pos.y));
	auto		end = _boostList.end();
	Coords		coord;

	if (_map.get(x, y) != MAP_TYPE_BOOST)
		return;
	for (auto it = _boostList.begin(); it != end; ++it) {
		coord = (*it)->getCoords();
		if (coord.x == x && coord.y == y) {
			(*it)->applyBoost(ent);
			_map.set(x, y, MAP_TYPE_EMPTY);
			_boostList.erase(it);
			Mixer::mixer.playEffectGrabBoost();
			break;
		}
	}
}

void	MapHandler::embraceWall(Pos_t &pos, bool onY)
{
	if (onY)
		pos.x = std::round(pos.x);
	else
		pos.y = std::round(pos.y);
}

void	MapHandler::actionCharacter(void)
{
	for (auto ent : _entlist) {
		try {
			ent->doAction(*this);
		} catch (Exception e) {};
	}
}

void	MapHandler::clearSpawn(void) noexcept
{
	_map.set(0, 0, MAP_TYPE_EMPTY);
	_map.set(0, 1, MAP_TYPE_EMPTY);
	_map.set(1, 0, MAP_TYPE_EMPTY);
	_map.set(_width - 1, 0, MAP_TYPE_EMPTY);
	_map.set(_width - 1, 1, MAP_TYPE_EMPTY);
	_map.set(_width - 2, 0, MAP_TYPE_EMPTY);
	_map.set(0, _heigth - 1, MAP_TYPE_EMPTY);
	_map.set(1, _heigth - 1, MAP_TYPE_EMPTY);
	_map.set(0, _heigth - 2, MAP_TYPE_EMPTY);
	_map.set(_width - 1, _heigth - 1, MAP_TYPE_EMPTY);
	_map.set(_width - 1, _heigth - 2, MAP_TYPE_EMPTY);
	_map.set(_width - 2, _heigth - 1, MAP_TYPE_EMPTY);
}

void	MapHandler::addFlame(int x, int y)
{
	auto	end = _entlist.end();
	Pos_t	position = {0, 0, 0};

	position.x = static_cast<float>(x);
	position.y = static_cast<float>(y);
	_flameList.push_back(new Flame(position));
	_map.set(x, y, MAP_TYPE_FLAME);
	for (auto it = _entlist.begin(); it < end; ++it) {
		if ((*it)->matchPosition(x, y))
			(*it)->kill();
	}
}

void	MapHandler::burnBoost(int x, int y)
{
	auto	end = _boostList.end();
	Coords	coord;

	for (auto it = _boostList.begin(); it != end; ++it) {
		coord = (*it)->getCoords();
		if (coord.x == x && coord.y == y) {
			_boostList.erase(it);
			break;
		}
	}
	addFlame(x, y);
}

void	MapHandler::breakBlock(int x, int y)
{
	int	randValue = rand() % 100;
	Pos_t	pos;
	ABoost	*get = nullptr;

	if (randValue <= BOOST_DROP_CHANCE) {
		get = ABoost::dropBoost();
		if (get == nullptr)
			throw Exception("An error occured "
			"during droping boost");
		pos.x = static_cast<float>(x);
		pos.y = static_cast<float>(y);
		pos.direction = 0;
		get->setPosition(pos);
		_boostList.push_back(get);
		_map.set(x, y, MAP_TYPE_BOOST);
	} else
		addFlame(x, y);
}

bool	MapHandler::spreadFlame(int x, int y)
{
	int	value;

	if (x < 0 || x >= _width || y < 0 || y >= _heigth)
		return false;
	value = _map.get(x, y);
	switch (value) {
		case MAP_TYPE_BLOC:
			breakBlock(x, y);
			return false;
		case MAP_TYPE_BOMB:
			chainExplosion(x, y);
			return false;
		case MAP_TYPE_BOOST:
			burnBoost(x, y);
			return true;
		case MAP_TYPE_WALL: return false;
		case MAP_TYPE_FLAME: return true;
	}
	addFlame(x, y);
	return true;
}

void	MapHandler::chainExplosion(int x, int y)
{
	try {
		findBomb(x, y).premature();
	} catch (Exception) {}
	_map.set(x, y, MAP_TYPE_FLAME);
}

void		MapHandler::createExplosion(Bomb &bomb)
{
	Pos_t	center = bomb.getPosition();
	int	power = bomb.getPower();

	Mixer::mixer.playEffectExplosion();
	_map.set(center, MAP_TYPE_EMPTY);
	addFlame(center.x, center.y);
	spreadExplosion(center, power, DIREC_UP);
	spreadExplosion(center, power, DIREC_DOWN);
	spreadExplosion(center, power, DIREC_LEFT);
	spreadExplosion(center, power, DIREC_RIGHT);
}

void		MapHandler::spreadExplosion(Pos_t pos, int power, int direction)
{
	int	posX = static_cast<int>(pos.x);
	int	posY = static_cast<int>(pos.y);

	posX += DIREC_GET_MOVE_X(direction);
	posY += DIREC_GET_MOVE_Y(direction);
	for (int it = 0; it < power; ++it) {
		if (spreadFlame(posX, posY) == false)
			break;
		posX += DIREC_GET_MOVE_X(direction);
		posY += DIREC_GET_MOVE_Y(direction);
	}
}

void	MapHandler::setWall(int x, int y) noexcept
{
	if (_map.get(x, y) == 1)
		return;
	if ((std::rand() % 100) <= 75)
		_map.set(x, y, MAP_TYPE_BLOC);
}

bool		MapHandler::isObstructed(ACharacter &player,
				Coords &base, Coords &next)
{
	int	baseValue;
	int	nextValue;

	if (base.x >= _width || base.y >= _heigth || base.x < 0
	|| base.y < 0 || next.x >= _width || next.y >= _heigth
	|| next.x < 0 || next.y < 0)
		return true;
	baseValue = _map.get(base);
	nextValue = _map.get(next);
	if (!isAllowedToPass(player, baseValue, nextValue))
		return true;
	if (baseValue != MAP_TYPE_BOMB && nextValue != MAP_TYPE_BOMB)
		player.leaveBomb();
	return false;
}

bool		MapHandler::isAllowedToPass(ACharacter &player,
						int base, int next)
{
	if (base == MAP_TYPE_WALL || next == MAP_TYPE_WALL)
		return false;
	if ((base == MAP_TYPE_BLOC || next == MAP_TYPE_BLOC)
	&& !player.canWallPass())
		return false;
	if ((base == MAP_TYPE_BOMB || next == MAP_TYPE_BOMB)
	&& !player.isInBomb())
		return false;
	return true;
}

bool		MapHandler::isValidMove(ACharacter &player, Pos_t &pos,
	bool onY)
{
	Coords	base = {static_cast<int>(std::floor(pos.x)),
			static_cast<int>(std::floor(pos.y))};
	Coords	next = base;

	if (onY) {
		if (fabs(std::round(pos.y) - pos.y) >= 0.001)
			return false;
		next.x = static_cast<int>(std::floor(pos.x + 1.0));
	} else {
		if (fabs(std::round(pos.x) - pos.x) >= 0.001)
			return false;
		next.y = static_cast<int>(std::floor(pos.y + 1.0));
	}
	return !isObstructed(player, base, next);
}

void		MapHandler::adaptPositions(Pos_t &pos, bool onY)
{
	float	calcPos;

	if (onY) {
		calcPos = std::round(pos.y);
		if (fabs(pos.y - calcPos) <= ENT_LARG_ERR)
			pos.y = calcPos;
	} else {
		calcPos = std::round(pos.x);
		if (fabs(pos.x - calcPos) <= ENT_LARG_ERR)
			pos.x = calcPos;
	}
}
