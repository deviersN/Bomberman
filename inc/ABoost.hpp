//
// EPITECH PROJECT, 2018
// indie
// File description:
// aboost
//

#ifndef ABOOST_HPP_
	#define ABOOST_HPP_

	class ABoost;

	#include "IEntity.hpp"
	#include "ACharacter.hpp"

	#include <array>

	class ABoost : public IEntity {
	public:
		ABoost(void);
		~ABoost(void);
		// Getters
		PowerUp_t	getType(void) const;
		const Coords	getCoords(void) const;
		Pos_t		getPosition(void) const;
		// Setters
		void	setPosition(const Pos_t &pos);
		// Methods
		virtual void	applyBoost(ACharacter &target) = 0;
		// Static methods
		static ABoost	*dropBoost(void);
	protected:
		PowerUp_t	_type = POWER_NONE;
		Pos_t		_pos;
	};

#endif /* !ABOOST_HPP_ */
