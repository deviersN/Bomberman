//
// EPITECH PROJECT, 2018
// indie
// File description:
// player
//

#ifndef PLAYER_HPP_
	#define PLAYER_HPP_

	#include "ACharacter.hpp"

	class Player : public ACharacter {
	public:
		Player(int id);
		~Player();
		// Getters
		bool	isMoving(void) const noexcept override;
		bool	isPlayer(void) const noexcept override;
		// Methods
		void	say(void) const noexcept override;
		void	doAction(MapHandler &map) override;
		// Static
		static	Action_t	g_actions[2];
	private:
		int	_id;
	};

#endif /* !PLAYER_HPP_ */
