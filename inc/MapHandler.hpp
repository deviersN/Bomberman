//
// EPITECH PROJECT, 2018
// indie
// File description:
// maphandler
//

#ifndef MAPHANDLER_HPP_
	#define MAPHANDLER_HPP_

	#include <iostream>
	#include <cstdint>
	#include <memory>
	#include <array>
	#include <vector>
	#include <list>

	// Forward declaration
	class MapHandler;

	#include "Map.hpp"
	#include "ACharacter.hpp"
	#include "Bomb.hpp"
	#include "Flame.hpp"
	#include "ABoost.hpp"

	using CharacterList = std::array<ACharacter*, ENT_AMOUNT>;
	using FlameList = std::list<Flame*>;
	using BombList = std::list<Bomb*>;
	using BoostList = std::vector<ABoost*>;

	class MapHandler {
	public:
		// Ctor Dtor
		MapHandler(void);
		~MapHandler(void);
		// Getters
	        Map			*getMap(void);
		const CharacterList	&getCharacterList(void) const;
		PowerUp_t		getBoostTypeAt(int x, int y) const;
		const ACharacter	&getCharacter(int id) const;
		int			getCaseValue(int x, int y) const;
		int			getWinner(void) const noexcept;
		bool			noPlayer(void);
		bool			isOver(void);
		BombList		getBombList(void);
		// Setters
		void	setMapValue(int x, int y, int value);
		void	setCharacterList(const CharacterList &list);
		// Methods
		void	turn(void);
		void	showMap(void) const noexcept;
		bool	addBomb(Pos_t pos, int power, ACharacter *owner);
		void	generate(int width, int heigth);
		void	clockBomb(void);
		void	playerSay(int id);
		void	moveEntity(int id, int direction);
		void	moveEntity(ACharacter &ent, int direction);
		void	initCharacters(int player_nb);
		void	destroyCharacters(void);
	private:
		// Private Methods
		Bomb	&findBomb(int x, int y);
		void	applyBoost(ACharacter &ent, const Pos_t &pos);
		void	embraceWall(Pos_t &pos, bool onY);
		void	actionCharacter(void);
		void	clearSpawn(void) noexcept;
		void	addFlame(int x, int y);
		void	burnBoost(int x, int y);
		void	breakBlock(int x, int y);
		bool	spreadFlame(int x, int y);
		void	chainExplosion(int x, int y);
		void	createExplosion(Bomb &bomb);
		void	spreadExplosion(Pos_t pos,
					int power, int direction);
		void	setWall(int x, int y) noexcept;
		bool	isObstructed(ACharacter &player,
					Coords &base, Coords &next);
		bool	isAllowedToPass(ACharacter &player,
					int base, int next);
		bool	isValidMove(ACharacter &ent, Pos_t &pos,
					bool onY);
		void	adaptPositions(Pos_t &pos, bool onY);
		// Attributs
		Map		_map;
		CharacterList	_entlist = {nullptr};
		BombList	_bomblist;
		FlameList	_flameList;
		BoostList	_boostList;
	        int		_width = 0;
		int	 	_heigth = 0;
		int		_winner = -1;
	};

#endif /* !MAPHANDLER_HPP_ */
