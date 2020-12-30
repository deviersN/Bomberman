//
// EPITECH PROJECT, 2018
// indie
// File description:
// loader
//

#include <iostream>
#include "Loader.hpp"
#include "Exception.hpp"
#include "SysMacro.hpp"

Loader::Loader(const char *path)
{
	std::string	prePath(path);
	size_t		idx = prePath.find_last_of(LAST_SLASH);

	_base = prePath.substr(0, idx);
	_base += BASE_ASSETS;
}

Loader::~Loader()
{
}

// Setters
void	Loader::setDriver(IVideoDriver *driver)
{
	_driver = driver;
}

void	Loader::setSceneManage(ISceneManager *manager)
{
	_smgr = manager;
}

void	Loader::setGuiEnvironment(IGUIEnvironment *env)
{
	_gui = env;
}

// Getters
ITexture	*Loader::getTexture(const std::string &path)
{
	ITexture	*ret = nullptr;
	std::string	fullPath = _base + path;

	if (!_driver)
		throw Exception("Can't load texture: No Driver");
	ret = _driver->getTexture(fullPath.c_str());
	if (ret == nullptr)
		throw Exception("Can't load texture '" + fullPath + "'");
	return ret;
}

IAnimatedMesh	*Loader::getMesh(const std::string &path)
{
	IAnimatedMesh	*ret = nullptr;
	std::string	fullPath = _base + path;

	if (!_smgr)
		throw Exception("Can't load mesh: No Scene Manager");
	ret = _smgr->getMesh(fullPath.c_str());
	if (ret == nullptr)
		throw Exception("Can't load mesh '" + fullPath + "'");
	return ret;
}

IGUIFont	*Loader::getFont(const std::string &path)
{
	IGUIFont	*ret = nullptr;
	std::string	fullPath = _base + path;

	if (!_gui)
		throw Exception("Can't load font: No GuiEnvironment");
	ret = _gui->getFont(fullPath.c_str());
	if (ret == nullptr)
		throw Exception("Can't load font '" + fullPath + "'");
	return ret;
}

const std::string	&Loader::getBase(void) const
{
	return this->_base;
}
