//
// EPITECH PROJECT, 2018
// indie
// File description:
// flame
//

#ifndef FLAME_HPP_
	#define FLAME_HPP_

	#include <chrono>

	#include "IEntity.hpp"

	class Flame : public IEntity {
	public:
		Flame(const Pos_t &pos);
		~Flame(void);
		// Methods
		bool	clock(void) noexcept;
		// Getters
		Pos_t	getPosition(void) const override;
		// Setters
		void	setPosition(const Pos_t &pos) override;
	private:
		using		timerType = std::chrono::time_point<std::chrono::system_clock>;
		Pos_t		_position;
		timerType	_start;
	};

#endif /* !FLAME_HPP_ */
