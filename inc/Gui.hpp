//
// EPITECH PROJECT, 2018
// indie
// File description:
// Gui menu
//

#ifndef GUI_HPP
	#define GUI_HPP

	class Gui;

	#include <cstdint>
	#include <irrlicht.h>
	#include <vector>
	#include "Parse.hpp"
	#include "MapHandler.hpp"
	#include "EventReceiver.hpp"
	#include "Loader.hpp"

	using EntTab = std::array<irr::scene::IAnimatedMeshSceneNode*,
							ENT_AMOUNT>;

	class Gui {
	public:
		// Ctor Dtor
		Gui(const char *base = "./");
		~Gui(void);
		// Methods
		void		getConf(void);
		void		createMyDevice(void);
		void		displayMenu(bool loop = true);
		void		displayOptions(void);
		void		displayButtonMenu(void);
		void		displayWinner(void);
		void		escape(bool shift);
		void		resetGame(void);
		void		loadMap(void);
		void		loadGame(const std::wstring &path);
		void		loadGameRessources(void);
		bool		gameActions(void);
		void		displayGame(bool loop = true);
		void		initEntities(void);
		void		initEntity(int id);
		void		placeEntities(void);
		void		applyAnimation(int id);
		void		applyTexture(int id);
		void		drawGameBackground(void);
		void		drawGameBlock(int x, int y);
		void		drawBoost(int x, int y, int idx);
		void		initGameBackground(void);
		void		initGameBlock(int x, int y);
		void		initBackBlock(int x, int y);
		void		destroyAll(void);
		void		handleKeys(bool index);
		void		addPlayButton(void);
		void		addResetButton(void);
		void		addPlayerButton(void);
		void		addLoadButton(void);
		void		addOptionsButton(void);
		void		addCommandsButton(void);
		void		addReturnButton(int id, int decal);
		void		addQuitButton(void);
		void		addPlusButton(int decal, int id);
		void		addLessButton(int decal, int id);
		void		setBackground(void);
		void		setVolumeHandler(void);
		void		setPlayerHandler(bool duo);
		void		setGameOff(void) noexcept;
		void		deviceRun(void);
		void		displayVolumeEffect(int change);
		void		displayVolumeMusic(int change);
		void		displayVolumeSprite(int decal);
		void		initPosVector(std::vector<int> &pos);
		void		initPathVector(
			std::vector<irr::io::path> &sprite);
		int		getVolumeEffect(void) const;
		int		getVolumeMusic(void) const;
	private:
		// Attributs
		Loader		_load;
		irr::IrrlichtDevice 			*_device = nullptr;
		irr::gui::IGUIEnvironment		*_guienv = nullptr;
		irr::video::IVideoDriver		*_driver = nullptr;
		irr::scene::ISceneManager		*_smgr = nullptr;
		int 					_sound = 0;
		bool					_game = false;
		irr::video::ITexture			*_outGameBlock;
		std::vector<irr::video::ITexture*>	_gameBlocks;
		std::vector<irr::video::ITexture*>	_gameBoosts;
		EntTab					_entities;
		std::array<bool, ENT_AMOUNT>		_walking = {false};
		irr::scene::IAnimatedMesh*		_gameCharacterWait;
		irr::scene::IAnimatedMesh*		_gameCharacterWalk;
		irr::scene::IAnimatedMesh*		_gameCharacterDab;
		irr::video::ITexture*			_gamePlayer1Texture;
		irr::video::ITexture*			_gamePlayer2Texture;
		irr::video::ITexture*			_gameNpcTexture;
		irr::gui::IGUIFont			*_font;
		std::vector<irr::scene::ISceneNode*>	_blocks;
		EventReceiver				*_receiver;
		MapHandler				_map;
		Key					_key[2];
		Sound_t					_sounds;
		bool					_duo = true;
		bool					_initedGame = false;
		bool					_valid = false;
		bool					_resetGame = true;
		Parse					_parser;
	};

#endif /* !GUI_HPP */
