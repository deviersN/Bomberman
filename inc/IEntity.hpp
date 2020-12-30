//
// EPITECH PROJECT, 2018
// indie
// File description:
// IEntity
//

#ifndef IENTITY_HPP_
	#define IENTITY_HPP_

	#include "Structure.hpp"

	class IEntity {
	public:
		IEntity(void) {};
		virtual ~IEntity(void) = default;
		// Getters
		virtual Pos_t	getPosition(void) const = 0;
		// Setters
		virtual void	setPosition(const Pos_t &pos) = 0;
	};

#endif /* !IENTITY_HPP_ */
