//
// EPITECH PROJECT, 2018
// indie
// File description:
// loader
//

#ifndef LOADER_HPP_
	#define LOADER_HPP_

	#include <irrlicht.h>
	#include <irrKlang.h>
	#include <string>

	using irr::video::IVideoDriver;
	using irr::scene::ISceneManager;
	using irr::video::ITexture;
	using irr::scene::IAnimatedMesh;
	using irr::gui::IGUIEnvironment;
	using irr::gui::IGUIFont;

	class Loader {
	public:
		// Ctor & Dtor
		Loader(const char *path);
		~Loader();
		// Setters
		void	setDriver(IVideoDriver *driver);
		void	setSceneManage(ISceneManager *manager);
		void	setGuiEnvironment(IGUIEnvironment *env);
		// Getters
		ITexture		*getTexture(const std::string &path);
		IAnimatedMesh		*getMesh(const std::string &path);
		IGUIFont		*getFont(const std::string &path);
		const std::string	&getBase(void) const;
	private:
		// Attributs
		std::string		_base;
		IVideoDriver		*_driver = nullptr;
		ISceneManager		*_smgr = nullptr;
		IGUIEnvironment		*_gui = nullptr;
	};

#endif /* !LOADER_HPP_ */
