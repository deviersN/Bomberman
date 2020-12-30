//
// EPITECH PROJECT, 2018
// Indie
// File description:
// DangerousMap
//

#ifndef DANGER_HPP_
	#define DANGER_HPP_

	#include <iostream>
	#include <vector>
	#include "Map.hpp"
	#include "Bomb.hpp"

	enum	zoneType
	{
		SAFE = 0,
		RISKNBORDER = 1,
		BOX = 2
	};

	class		Danger : public Map
	{
	public:
		Danger(std::size_t height, std::size_t width);
		~Danger(void);
	public:
		void	dropBombs(
			std::vector<Bomb*> explosiveBelt, Map *casualMap);
		int	**getDangerMap(void);
	private:
		void	evaluateDanger(Bomb *bomb, Map *casualMap);
	};

#endif /* DANGER_HPP_ */
