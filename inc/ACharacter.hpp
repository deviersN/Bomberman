//
// EPITECH PROJECT, 2018
// indie
// File description:
// ACharacter
//

#ifndef ACHARACTER_HPP_
	#define ACHARACTER_HPP_

	// Forward declaration
	class ACharacter;

	#include "IEntity.hpp"
	#include "MapHandler.hpp"

	class ACharacter : public IEntity {
	public:
		ACharacter(void);
		~ACharacter(void) override;
		// Getters
		bool		isAlive(void) const noexcept;
		bool		isInBomb(void) const noexcept;
		int		getBombMax(void) const noexcept;
		float		getPower(void) const noexcept;
		bool		canWallPass(void) const noexcept;
		Pos_t		getPosition(void) const override;
		EntData_t	getEntData(void) const;
		float		getSpeed(void) const noexcept;
		virtual bool	isMoving(void) const noexcept = 0;
		virtual bool	isPlayer(void) const noexcept = 0;
		// Setters
		void		setAlive(const bool &alive);
		void		setPosition(const Pos_t &pos) override;
		void		setBombMax(const int &nbBomb);
		void		setPower(const float &power);
		void		setWallPass(const bool &canWallPass);
		void		setSpeed(const float &speed);
		void		setEntData(const EntData_t &data);
		void		leaveBomb(void) noexcept;
		// Methods
		virtual void	say(void) const noexcept = 0;
		virtual void	doAction(MapHandler &map) = 0;
		void		kill(void) noexcept;
		bool		matchPosition(int x, int y) const noexcept;
		void		reducePlacedBomb(void) noexcept;
		// Boosts
		void		bombUp(void) noexcept;
		void		empower(void) noexcept;
		void		wallPass(void) noexcept;
		void		accelerate(void) noexcept;
	protected:
		// Protected methods
		void		moving(MapHandler &map, int direction);
		void		placeBomb(MapHandler &map);
		// Protected attributs
		EntData_t	_data;
		bool		_alive = true;
		bool		_inBomb = true;
		int		_placedBomb = 0;
	};

#endif /* !ACHARACTER_HPP_ */
