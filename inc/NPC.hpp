//
// EPITECH PROJECT, 2018
// Indie
// File description:
// NPC
//

#ifndef NPC_HPP_
	#define NPC_HPP_

	#include "ACharacter.hpp"
	#include "Danger.hpp"

	class			Npc : public ACharacter {
	public:
		Npc(int id);
		~Npc(void) override;
	public:
		void		say(void) const noexcept override;
		bool		isMoving(void) const noexcept override;
		void		doAction(MapHandler &map) override;
		Action_t	behaviour(Map *map);
		Action_t        newDirection(Map *map);
		Action_t        turnOver(Action_t dir);
		bool		stuckToBloc(Map *map);
		Action_t	findAWay(Map *map, Action_t lastAction);
		bool		isPlayer(void) const noexcept override;
	private:
		int		_id;
		Danger		*_riskzone;
	};

#endif /* !_HPP_ */
