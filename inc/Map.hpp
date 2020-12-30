//
// EPITECH PROJECT, 2018
// indie
// File description:
// map
//

#ifndef MAP_HPP_
	#define MAP_HPP_

	#include "Structure.hpp"

	class Map {
	public:
		// Ctor & Dtor
		Map(void);
		~Map(void);
		// Getters
		int	getW() const;
		int	getH() const;
		int	get(const Pos_t &pos) const;
		int	get(const Coords &pos) const;
		int	get(int x, int y) const;
		int	getNE(int x, int y) const noexcept;
		// Setters
		void	set(const Pos_t &pos, int value) throw();
		void	set(const Coords &pos, int value) throw();
		void	set(int x, int y, int value) throw();
		// Methods
		void	destroy(void) throw();
		void	create(int width, int height);
	protected:
		// Private Methods
		// Attributs
		// -> IEntity data
		int		_width = 0;
		int		_height = 0;
		int		**_map = nullptr;
	};

#endif /* !MAP_HPP_ */
