//
// EPITECH PROJECT, 2018
// Parse
// File description:
// cpp
//

#include <unordered_map>
#include <sstream>
#include <memory>
#include <string>
#include "Open.hpp"
#include "stdlib.h"
#include "Parse.hpp"
#include "Exception.hpp"

/*
**      /------------\
**      | Key String |
**      \------------/
*/

#define MAX_K	irr::KEY_KEY_CODES_COUNT

static std::unordered_map<std::string, irr::EKEY_CODE>	keyString = {
	{"up", irr::KEY_UP}, {"down", irr::KEY_DOWN},
	{"left", irr::KEY_LEFT}, {"right", irr::KEY_RIGHT},
	{"rctrl", irr::KEY_RCONTROL}
};

/*
**      /--------\
**      | Public |
**      \--------/
*/

Parse::Parse(const char *path)
{
	std::size_t	x = 0;
	std::size_t	y = 0;

	if (path == NULL)
		_path = "./";
	while (path[y] != '\0') {
		if (path[y] == '/')
			x = y + 1;
		y++;
	}
	_path = path;
	_map = path;
	_map.replace(x, y - x, "save/");
	_path.replace(x, y - x, "conf/");
}

Parse::~Parse()
{
}

void	Parse::saveMap(MapHandler &map)
{
	std::ofstream	file(_map + std::string("map.save"));
	Map		*content = map.getMap();
	CharacterList	list = map.getCharacterList();
	int		nbPlayer = 0;

	printMap(content, file);
	for (std::size_t i = 0; i < list.size(); i++)
		if (list[i]->isPlayer() == true)
			nbPlayer++;
	if (nbPlayer > 2 || nbPlayer == 0)
		nbPlayer = 1;
	file << "#" << nbPlayer << std::endl;
	for (std::size_t i = 0; i < list.size(); i++)
		printCharacter(list[i], file);
}

bool	Parse::loadMap(MapHandler &map, const std::string &fileName)
{
	Open				file(_map + fileName);
	std::vector<std::string>	content = file.getContent();
	int				nbPlayer;
	CharacterList			list;

	if (content.size() < 11 + 4 + 1 || !goodMap(content))
		throw Exception("Error: Corrupted file: save/map.save");
	nbPlayer = content[11][1] - '0';
	fillMap(map, content);
	for (std::size_t i = 0; i < 4; i++)
		if (i < nbPlayer)
			list[i] = getPlayer(content[i + 12], i);
		else
			list[i] = getNpc(content[i + 12], i);
	map.destroyCharacters();
	map.setCharacterList(list);
	return (nbPlayer + 1) % 2;
}

Key	Parse::getKey(bool index)
{
	Open				file("key.conf", _path);
	std::vector<std::string>	content = file.getContent();
	std::string			player = playerId(index);
	std::size_t			i;
	Key				ret = keyCreate();

	if (content.size() != 12)
		printCorruptedFile("key.conf");
	for (i = 1; i < content.size()
			&& content[i - 1].compare(player); i++);
	for (std::size_t y = 1; y <= 5 && i < content.size(); y++) {
		lineContent(content[i], ret);
		i++;
	}
	return defaultKey(index, ret);
}

Sound_t	Parse::getSound(void)
{
	Open				file("sound.conf", _path);
	std::vector<std::string>	content = file.getContent();
	Sound_t				ret = soundCreate();

	if (content.size() != 2)
		printCorruptedFile("sound.conf");
	for (std::size_t i = 0; i < content.size(); i++) {
		if (content[i].compare(0, 6, "music:") == 0 &&
		content[i][6] >= '0' && content[i][6] <= '9' &&
		content[i][7] == '\0')
			ret.music = content[i][6] - '0';
		if (content[i].compare(0, 6, "sound:") == 0 &&
		content[i][6] >= '0' && content[i][6] <= '9' &&
		content[i][7] == '\0')
			ret.soundEffect = content[i][6] - '0';
	}
	if (content.size() == 2 && (ret.music == -1 || ret.soundEffect == -1))
		printCorruptedFile("Sound.conf");
	return defaultSound(ret);
}

void	Parse::setSound(Sound_t sound) const
{
	std::ofstream	outfile(_path + "sound.conf");

	outfile << "music:" << sound.music << std::endl
		<< "sound:" << sound.soundEffect << std::endl;
	outfile.close();
}

/*
**      /---------\
**      | Private |
**      \---------/
*/

std::string	Parse::playerId(bool index)
{
	std::string	player = "Px:";

	player[1] = index + 1 + '0';
	return player;
}

bool	Parse::goodMap(std::vector<std::string> content)
{
	for (std::size_t x = 0; x < 11; x++) {
		if (content[x].size() != 11)
			return false;
		for (std::size_t y = 0; y < 11; y++)
			if (content[x][y] < MAP_TYPE_BOOST + '0' ||
			    content[x][y] > MAP_TYPE_BOMB + '0')
				return false;
	}
	if (content[11].compare("#1\0") == 0 ||
	    content[11].compare("#2\0") == 0)
		return true;
	return false;
}

bool	Parse::isKey(irr::EKEY_CODE key)
{
	bool	ret = false;

	if (key >= irr::KEY_LEFT && key <= irr::KEY_DOWN)
		ret = true;
	if (key >= irr::KEY_KEY_A && key <= irr::KEY_KEY_Z)
		ret = true;
	if (key == irr::KEY_SPACE || key == irr::KEY_RCONTROL)
		ret = true;
	return ret;
}

Key	Parse::keyCreate(void)
{
	Key	ret;

	ret.up = MAX_K;
	ret.down = MAX_K;
	ret.left = MAX_K;
	ret.right = MAX_K;
	ret.drop = MAX_K;
	return ret;
}

Key	Parse::defaultKey(bool index, Key ret)
{
	if (!index) {
		ret.up = (!isKey(ret.up)) ? irr::KEY_KEY_Z : ret.up;
		ret.down = (!isKey(ret.down)) ? irr::KEY_KEY_S : ret.down;
		ret.left = (!isKey(ret.left)) ? irr::KEY_KEY_Q : ret.left;
		ret.right = (!isKey(ret.right)) ? irr::KEY_KEY_D : ret.right;
		ret.drop = (!isKey(ret.drop)) ? irr::KEY_KEY_F : ret.drop;
	} else {
		ret.up = (!isKey(ret.up)) ? keyString["up"] : ret.up;
		ret.down = (!isKey(ret.down)) ? keyString["down"] : ret.down;
		ret.left = (!isKey(ret.left)) ? keyString["left"] : ret.left;
		ret.right = (!isKey(ret.right)) ? keyString["right"] : ret.right;
		ret.drop = (!isKey(ret.drop)) ? keyString["rctrl"] : ret.drop;
	}
	return ret;
}

Sound_t	Parse::soundCreate(void)
{
	Sound_t	ret;

	ret.music = -1;
	ret.soundEffect = -1;
	return ret;
}

Sound_t	Parse::defaultSound(Sound_t ret)
{
	if (ret.music == -1 || ret.music > 5)
		ret.music = 3;
	if (ret.soundEffect == -1 || ret.soundEffect > 5)
		ret.soundEffect = 3;
	return ret;
}

Pos_t	Parse::verifPos(float x, float y)
{
	Pos_t	ret;

	ret.x = x;
	ret.y = y;
	ret.direction = DIREC_DOWN;
	if (x < static_cast<float>(0.0) || x > static_cast<float>(10.0))
		ret.x = 0.0;
	if (x < static_cast<float>(0.0) || x > static_cast<float>(10.0))
		ret.y = 0.0;
	return ret;
}

Player	*Parse::getPlayer(std::string str, int id)
{
	Pos_t			pos;
	Player			*ret = new Player(id);
	std::string		buf;
	std::stringstream	ss(str);
	std::vector<std::string> tokens;

	while (ss >> buf)
		tokens.push_back(buf);
	if (tokens.size() != 7)
		return ret;
	ret->setAlive(atoi(tokens[0].c_str()) % 2);
	ret->setPosition(verifPos(stof(tokens[1]), stof(tokens[2])));
	ret->setBombMax(atoi(tokens[3].c_str()));
	ret->setPower(stof(tokens[4]));
	ret->setWallPass(atoi(tokens[5].c_str()) % 2);
	ret->setSpeed(stof(tokens[6]));
	return ret;
}

Npc	*Parse::getNpc(std::string str, int id)
{
	Pos_t			pos;
	Npc			*ret = new Npc(id);
	std::string		buf;
	std::stringstream	ss(str);
	std::vector<std::string> tokens;

	while (ss >> buf)
		tokens.push_back(buf);
	if (tokens.size() != 7)
		return ret;
	ret->setAlive(atoi(tokens[0].c_str()) % 2);
	ret->setPosition(verifPos(stof(tokens[1]), stof(tokens[2])));
	ret->setBombMax(atoi(tokens[3].c_str()));
	ret->setPower(stof(tokens[4]));
	ret->setWallPass(atoi(tokens[5].c_str()) % 2);
	ret->setSpeed(stof(tokens[6]));
	return ret;
}

void	Parse::printMap(Map *map, std::ofstream &file)
{
	for (std::size_t x = 0; x < 11; x++) {
		for (std::size_t y = 0; y < 11; y++) {
			if (map->get(y, x) == MAP_TYPE_FLAME ||
			    map->get(y, x) == MAP_TYPE_BOOST ||
			    map->get(y, x) == MAP_TYPE_BOMB)
				file << '0';
			else
				file << map->get(y, x);
				
		}
		file << std::endl;
	}
}

void	Parse::printCharacter(ACharacter *character, std::ofstream &file)
{
	file << character->isAlive() << " "
	     << character->getPosition().x << " "
	     << character->getPosition().y << " "
	     << character->getBombMax() << " "
	     << character->getPower() << " "
	     << character->canWallPass() << " "
	     << character->getSpeed() << std::endl;
}

void	Parse::fillMap(MapHandler &map, std::vector<std::string> content)
{
	map.generate(11, 11);
	for (std::size_t x = 0; x < 11; x++)
		for (std::size_t y = 0; y < 11; y++)
			if (content[x][y] - '0' != MAP_TYPE_FLAME &&
			    content[x][y] - '0' != MAP_TYPE_BOMB)
				map.setMapValue(y, x, content[x][y] - '0');
}

void	Parse::keyContent(std::string str, irr::EKEY_CODE &key)
{
	bool	done = false;

	for (auto it = keyString.begin(); it != keyString.end(); it++) {
		if (str.compare(it->first) == 0) {
			key = it->second;
			done = true;
		}
	}
	if (!done) {
		key = static_cast<irr::EKEY_CODE>(str[0]);
		if (key >= 'a' && key <= 'z')
			key = static_cast<irr::EKEY_CODE>
				(static_cast<int>(key) - 'a' - 'A');
	}
}

void	Parse::lineContent(std::string str, Key &ret)
{
	if (str.compare(0, 3, "up:") == 0)
		keyContent(str.substr(3), ret.up);
	if (str.compare(0, 5, "down:") == 0)
		keyContent(str.substr(5), ret.down);
	if (str.compare(0, 5, "left:") == 0)
		keyContent(str.substr(5), ret.left);
	if (str.compare(0, 6, "right:") == 0)
		keyContent(str.substr(6), ret.right);
	if (str.compare(0, 5, "drop:") == 0)
		keyContent(str.substr(5), ret.drop);
}

void	Parse::printCorruptedFile(std::string file)
{
	std::cout << file << " is corrupted" << std::endl
		<< "Please make sure the file contain right information"
		<< std::endl;
}
