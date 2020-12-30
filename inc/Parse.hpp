//
// EPITECH PROJECT, 2018
// Parse
// File description:
// hpp
//

#ifndef PARSE_HPP_
	#define PARSE_HPP_

	#include <vector>
	#include <string>
	#include <fstream>
	#include <iostream>
	#include <stdbool.h>
	#include "Key.hpp"
	#include "NPC.hpp"
	#include "Player.hpp"
	#include "Structure.hpp"
	#include "ACharacter.hpp"
	#include "MapHandler.hpp"

	class Parse {
	public:
		// Ctor Dtor
		Parse(const char *path);
		~Parse();
		// Getters
		void	saveMap(MapHandler &map);
	        bool	loadMap(MapHandler &map, const std::string &fileName = "./save/map.save");
		Key	getKey(bool index);
		Sound_t	getSound(void);
		// Setters
		void	setSound(Sound_t sound) const;
	private:
		// Private Methods
		std::string	playerId(bool index);
		bool		goodMap(std::vector<std::string> content);
		bool		isKey(irr::EKEY_CODE);
		Key		keyCreate(void);
		Key		defaultKey(bool index, Key ret);
		Sound_t		soundCreate(void);
		Sound_t		defaultSound(Sound_t ret);
		Pos_t		verifPos(float x, float y);
	        Player		*getPlayer(std::string str, int id);
		Npc		*getNpc(std::string str, int id);
		void		printMap(Map *map, std::ofstream &file);
		void		printCharacter(ACharacter *character, std::ofstream &file);
		void		fillMap(MapHandler &map, std::vector<std::string> content);
		void		keyContent(std::string, irr::EKEY_CODE &pos);
		void		lineContent(std::string str, Key &ret);
		void		printCorruptedFile(std::string file);
		// Attributs
		std::vector<std::string>	_sound;
		std::vector<std::string>	_key;
		std::string			_path;
		std::string			_map;
	};

#endif /* !PARSE_HPP_ */
