//
// EPITECH PROJECT, 2018
// indie
// File description:
// boost wallpass
//

#ifndef BOOSTWALLPASS_HPP_
	#define BOOSTWALLPASS_HPP_

	#include "ABoost.hpp"

	class BoostWallPass : public ABoost {
	public:
		BoostWallPass(void);
		~BoostWallPass(void);
		// Methods
		void	applyBoost(ACharacter &target) override;
	};

#endif /* !BOOSTWALLPASS_HPP_ */
