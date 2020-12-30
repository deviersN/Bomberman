//
// EPITECH PROJECT, 2018
// indie
// File description:
// map
//

#include "Map.hpp"
#include "Exception.hpp"

// Ctor & Dtor
Map::Map(void)
{
}

Map::~Map(void)
{
	if (_map != nullptr)
		this->destroy();
}

// Getters
int	Map::getW() const
{
	return this->_width;
}

int	Map::getH() const
{
	return this->_height;
}

int	Map::get(const Pos_t &pos) const
{
	return this->get(pos.x, pos.y);
}

int	Map::get(const Coords &pos) const
{
	return this->get(pos.x, pos.y);
}

int	Map::get(int x, int y) const
{
	if (x >= _width || y >= _height)
		throw Exception("Value out of bounds");
	return _map[y][x];
}

int	Map::getNE(int x, int y) const noexcept
{
	try {
		this->get(x, y);
	} catch (Exception e) {};
	return MAP_TYPE_WALL;
}

// Setters
void	Map::set(const Pos_t &pos, int value) throw()
{
	this->set(pos.x, pos.y, value);
}

void	Map::set(const Coords &pos, int value) throw()
{
	this->set(pos.x, pos.y, value);
}

void	Map::set(int x, int y, int value) throw()
{
	if (x >= _width || y >= _height)
		throw Exception("Value out of bounds");
	_map[y][x] = value;
}

// Methods
void	Map::destroy(void) throw()
{
	if (_map == nullptr)
		throw Exception("No map to destroy");
	for (int it = 0; it < _width; ++it)
		delete _map[it];
	delete _map;
}

void	Map::create(int width, int height)
{
	if (_map != nullptr)
		this->destroy();
	if (width * height < 4)
		throw Exception("Invalid map size");
	_width = width;
	_height = height;
	_map = new int*[height];
	for (int ith = 0; ith < height; ++ith) {
		_map[ith] = new int[width];
		for (int itw = 0; itw < width; ++itw) {
			_map[ith][itw] = ((itw % 2) && (ith % 2));
		}
	}
}
