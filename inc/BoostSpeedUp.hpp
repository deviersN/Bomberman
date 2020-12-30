//
// EPITECH PROJECT, 2018
// indie
// File description:
// boost speedup
//

#ifndef BOOSTSPEEDUP_HPP_
	#define BOOSTSPEEDUP_HPP_

	#include "ABoost.hpp"

	class BoostSpeedUp : public ABoost {
	public:
		BoostSpeedUp(void);
		~BoostSpeedUp(void);
		// Methods
		void	applyBoost(ACharacter &target) override;
	};

#endif /* !BOOSTSPEEDUP_HPP_ */
