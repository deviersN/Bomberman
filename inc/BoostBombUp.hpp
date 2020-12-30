//
// EPITECH PROJECT, 2018
// indie
// File description:
// boost bombup
//

#ifndef BOOSTBOMBUP_HPP_
	#define BOOSTBOMBUP_HPP_

	#include "ABoost.hpp"

	class BoostBombUp : public ABoost {
	public:
		BoostBombUp(void);
		~BoostBombUp(void);
		// Methods
		void	applyBoost(ACharacter &target) override;
	};

#endif /* !BOOSTBOMBUP_HPP_ */
