//
// EPITECH PROJECT, 2018
// indie
// File description:
// boost fireup
//

#ifndef BOOSTFIREUP_HPP_
	#define BOOSTFIREUP_HPP_

	#include "ABoost.hpp"

	class BoostFireUp : public ABoost {
	public:
		BoostFireUp(void);
		~BoostFireUp(void);
		// Methods
		void	applyBoost(ACharacter &target) override;
	};

#endif /* !BOOSTFIREUP_HPP_ */
