//
// EPITECH PROJECT, 2018
// indie
// File description:
// Bomb
//

#ifndef BOMB_HPP_
	#define BOMB_HPP_

	#include <chrono>

	class Bomb;

	#include "IEntity.hpp"
	#include "ACharacter.hpp"

	class Bomb : public IEntity {
	public:
		Bomb(const Pos_t &pos, int power, ACharacter *owner);
		~Bomb(void);
		// Methods
		bool	clock(void) noexcept;
		void	premature(void) noexcept;
		void	reduceOwner(void) noexcept;
		// Getters
		int	getPower(void) const noexcept;
		Pos_t	getPosition(void) const override;
		// Setters
		void	setPosition(const Pos_t &pos) override;
	private:
		using	timerType = std::chrono::time_point<std::chrono::system_clock>;
		int		_power;
		Pos_t		_position;
		ACharacter	*_owner;
		timerType	_start;
		bool		_prematured = false;
	};

#endif /* !BOMB_HPP_ */
