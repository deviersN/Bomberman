//
// EPITECH PROJECT, 2018
// indie
// File description:
// Gui Menu
//

#include <iostream>
#include <irrlicht.h>
#include <string.h>
#include <vector>
#include "Gui.hpp"
#include "EventReceiver.hpp"
#include "Exception.hpp"
#include "Player.hpp"
#include "Mixer.hpp"
#include "Parse.hpp"
#include "Key.hpp"
#include "SysMacro.hpp"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

Gui::Gui(const char *base) : _load(base), _parser(base)
{
	getConf();
	Mixer::mixer.initializeMixer(_load.getBase(), _sounds);
	try {
		createMyDevice();
		_valid = true;
	} catch (Exception e) {
		std::cout << e.what() << std::endl;
	}
}

Gui::~Gui()
{
}

void	Gui::getConf(void)
{
	_key[0] = _parser.getKey(0);
	_key[1] = _parser.getKey(1);
	_sounds = _parser.getSound();
}

void 	Gui::createMyDevice(void)
{
	_device = irr::createDevice(irr::video::EDT_OPENGL,
			irr::core::dimension2d<irr::u32>(1920, 1080), 16,
			false, true, true, 0);
	if (!_device)
		throw Exception("Cannot create device");
	_driver = _device->getVideoDriver();
	_smgr = _device->getSceneManager();
	_guienv = _device->getGUIEnvironment();
	if (!_driver || !_smgr || !_guienv)
		throw Exception("Cannot create drivers");
	_device->setWindowCaption(L"Bomberman");
	_smgr->addCameraSceneNode(0, irr::core::vector3df(0,0,-100),
					irr::core::vector3df(0,0,0));
	_device->setResizable(true);
	_receiver = new EventReceiver(_device, this);
	_load.setDriver(_driver);
	_load.setSceneManage(_smgr);
	_load.setGuiEnvironment(_guienv);
	loadGameRessources();
}

void Gui::deviceRun(void)
{
	while(_device->run())
	{
		_driver->beginScene(true, true, irr::video::SColor(255,0,0,0));
		irr::u32 time = _device->getTimer()->getTime();
		_smgr->drawAll();
		_guienv->drawAll();
		if (_game && gameActions()) {
			displayWinner();
		}
		_driver->endScene();
	}
}

/*
** Affiche le titre du jeu en haut, ainsi que le fond.
*/
void 	Gui::setBackground(void)
{
	_guienv->addImage(_load.getTexture(BACKGROUND_MENU),
			irr::core::position2d<int>(0,0));
	_guienv->addImage(_load.getTexture("gui/Title.png"),
			irr::core::position2d<int>(TITLE_POS_X, TITLE_POS_Y));
}

/*
** Affiche le menu du jeu
*/
void	Gui::displayMenu(bool loop)
{
	if (!_valid)
		throw Exception("An error occured during construction");
	Mixer::mixer.playMusicMenu();
	_guienv->clear();
	_font = _guienv->addFont("font",
			_load.getFont("Font/font_size_30.png"));
	if (!_font)
		throw Exception("Can't load font");
	setBackground();
	addPlayButton();
	if (_resetGame)
		setPlayerHandler(false);
	else
		addResetButton();
	addLoadButton();
	addOptionsButton();
	addQuitButton();
	_device->setEventReceiver(_receiver);
	if (loop)
		deviceRun();
}

/*
** Affiche le menu option
*/
void	Gui::displayOptions(void)
{
	_guienv->clear();
	setBackground();
	setVolumeHandler();
	addCommandsButton();
	addReturnButton(EventReceiver::GUI_ID_RETURN_BUTTON, 0);
}

/*
** Affiche les touches de jeux
*/
void 	Gui::displayButtonMenu(void)
{
	_guienv->clear();
	_guienv->addImage(_load.getTexture(BACKGROUND_MENU_COMMANDS),
			irr::core::position2d<int>(0,0));
	_guienv->addImage(_load.getTexture("gui/Title.png"),
			irr::core::position2d<int>(TITLE_COMMANDS_POS_X, TITLE_COMMANDS_POS_Y));
	addReturnButton(EventReceiver::GUI_ID_RETURN_OPT_BUTTON, 220);
}

void	Gui::displayWinner(void)
{
	int			winner = _map.getWinner();
	irr::video::SColor	color;

	if (winner != -1) {
		_entities[winner]->setMesh(_gameCharacterDab);
		applyTexture(winner);
		if (winner == 0 || (winner == 1 && _duo)) {
			color = irr::video::SColor(255, 100, 255, 100);
			Mixer::mixer.playEffectWin();
		} else {
			color = irr::video::SColor(255, 200, 50, 50);
			Mixer::mixer.playEffectLose();
		}
	} else
		color = irr::video::SColor(255, 200, 200, 50);
	addReturnButton(EventReceiver::GUI_ID_RETURN_WINNER, 0);
	while (_device->run() && _game) {
		_driver->beginScene(true, true, color);
		_smgr->drawAll();
		_guienv->drawAll();
		_map.turn();
		drawGameBackground();
		_driver->endScene();
	}
	_resetGame = true;
	displayMenu(false);
}

void	Gui::escape(bool shift)
{
	if (_game && !shift) {
		_resetGame = false;
		_game = false;
		displayMenu(false);
	} else
		_device->closeDevice();
}

void	Gui::resetGame(void)
{
	_resetGame = true;
	displayMenu(false);
}

void	Gui::loadMap(void)
{
	//auto dialog = _guienv->addFileOpenDialog(L"Select save file path",
	//			true, 0, -1, true);
	// Dialog segfaulting
	loadGame(L"map.save");
}

void	Gui::loadGame(const std::wstring &path)
{
	std::string	newPath(path.begin(), path.end());

	std::cout << "Loading: " << newPath << std::endl;
	try {
		_duo = _parser.loadMap(_map, newPath);
		_resetGame = false;
		displayGame(false);
	} catch (Exception e) {
		std::cerr << e.what() << std::endl;
		Mixer::mixer.playEffectLose();
	}
}

void	Gui::loadGameRessources(void)
{
	// Blocks texture
	_outGameBlock = _load.getTexture("Game/map_out.png");
	_gameBlocks.push_back(_load.getTexture("Game/map_fire.png"));
	_gameBlocks.push_back(_load.getTexture("Game/map_grass.jpeg"));
	_gameBlocks.push_back(_load.getTexture("Game/map_wall.png"));
	_gameBlocks.push_back(_load.getTexture("Game/map_block.png"));
	_gameBlocks.push_back(_load.getTexture("Game/map_bomb.png"));
	// Boosts texture
	_gameBoosts.push_back(_load.getTexture("Game/boost_power.png"));
	_gameBoosts.push_back(_load.getTexture("Game/boost_speed.png"));
	_gameBoosts.push_back(_load.getTexture("Game/boost_bomb.png"));
	_gameBoosts.push_back(_load.getTexture("Game/boost_wallpass2.png"));
	// Charactere textures
	_gameCharacterWait = _load.getMesh("Game/character_wait.md3");
	_gameCharacterWalk = _load.getMesh("Game/character_walk.md3");
	_gameCharacterDab = _load.getMesh("Game/character_dab.md3");
	_gamePlayer1Texture = _load.getTexture("Game/alex.png");
	_gamePlayer2Texture = _load.getTexture("Game/steve.png");
	_gameNpcTexture = _load.getTexture("Game/zombie.png");
}

bool	Gui::gameActions(void)
{
	_guienv->clear();
	handleKeys(0);
	if (_duo)
		handleKeys(1);
	_map.turn();
	placeEntities();
	drawGameBackground();
	if (_map.isOver()) {
		_resetGame = true;
		return true;
	}
	return false;
}

void	Gui::displayGame(bool loop)
{
	_game = true;
	Mixer::mixer.playMusicGame();
	if (_resetGame) {
		_map.generate(11, 11);
		_map.destroyCharacters();
		_map.initCharacters(1 + static_cast<int>(_duo));
	}
	initEntities();
	if (!_initedGame) {
		placeEntities();
		initGameBackground();
	}
	_initedGame = true;
	if (loop) {
		_guienv->clear();
		deviceRun();
	}
}

void	Gui::initEntities(void)
{
	for (int it = 0; it < ENT_AMOUNT; ++it) {
		if (!_initedGame) {
			_entities[it] = _smgr->addAnimatedMeshSceneNode(
							_gameCharacterWait);
		}
		if (_entities[it] == nullptr)
			throw Exception("Can't create entity");
		initEntity(it);
	}
}

void	Gui::initEntity(int id)
{
	_entities[id]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_entities[id]->setScale(irr::core::vector3df(1.3, 1.3, 1.3));
	_entities[id]->setVisible(true);
	applyTexture(id);
}

void	Gui::placeEntities(void)
{
	auto	entities = _map.getCharacterList();
	int	rotation;
	Pos_t	pos;

	for (int it = 0; it < ENT_AMOUNT; ++it) {
		pos = entities[it]->getPosition();
		pos.x = 10 * pos.x - 55;
		pos.y = 55 - 10 * pos.y;
		rotation = pos.direction;
		applyAnimation(it);
		if (rotation / 2 == -1)
			rotation = 180;
		rotation += (rotation % 2 * -90);
		_entities[it]->setRotation(
			irr::core::vector3df(-90, 0, rotation));
		_entities[it]->setPosition(
			irr::core::vector3df(pos.x, pos.y, 0));
	}
}

void	Gui::applyAnimation(int id)
{
	const ACharacter	&ent = _map.getCharacter(id);
	bool			walking = ent.isMoving();

	if (!ent.isAlive())
		_entities[id]->setVisible(false);
	if (walking) {
		if (!_walking[id]) {
			_entities[id]->setMesh(_gameCharacterWalk);
			_walking[id] = true;
			applyTexture(id);
		}
	} else {
		if (_walking[id]) {
			_entities[id]->setMesh(_gameCharacterWait);
			_walking[id] = false;
			applyTexture(id);
		}
	}
}

void	Gui::applyTexture(int id)
{
	if (id == 0)
		_entities[id]->setMaterialTexture(0,
					_gamePlayer1Texture);
	else if (id == 1 && _duo)
		_entities[id]->setMaterialTexture(0,
					_gamePlayer2Texture);
	else
		_entities[id]->setMaterialTexture(0,
					_gameNpcTexture);
}

void	Gui::drawGameBackground(void)
{
	for (int ity = 0; ity < 11; ++ity) {
		for (int itx = 0; itx < 11; ++itx) {
			drawGameBlock(itx, ity);
		}
	}
}

void	Gui::drawGameBlock(int x, int y)
{
	int	idx = 11 * y + x;
	int	value = _map.getCaseValue(x, y);

	if (value == MAP_TYPE_EMPTY)
		_blocks[idx]->setVisible(false);
	else if (value == MAP_TYPE_BOOST)
		drawBoost(x, y, idx);
	else {
		_blocks[idx]->setVisible(true);
		++value;
		_blocks[idx]->setMaterialTexture(0, _gameBlocks[value]);
	}
}

void	Gui::drawBoost(int x, int y, int idx)
{
	PowerUp_t	type;

	type = _map.getBoostTypeAt(x, y);
	if (type != POWER_NONE) {
		_blocks[idx]->setVisible(true);
		_blocks[idx]->setMaterialTexture(0,
					_gameBoosts[(int) type]);
	} else
		_blocks[idx]->setVisible(false);
}

void	Gui::initGameBackground(void)
{
	for (int ity = -1; ity <= 11; ++ity) {
		for (int itx = -1; itx <= 11; ++itx) {
			initGameBlock(itx, ity);
		}
	}
}

void	Gui::initGameBlock(int x, int y)
{
	const irr::core::vector3df	pos(10 * x - 55, 55 - 10 * y, 0);
	irr::scene::ISceneNode		*block;
	int				value = -5;

	block = _smgr->addCubeSceneNode();
	if (block == nullptr)
		throw Exception("Block not created");
	if (value == MAP_TYPE_EMPTY)
		block->setVisible(false);
	else if (value == -5)
		block->setMaterialTexture(0, _outGameBlock);
	else
		block->setMaterialTexture(0, _gameBlocks[value + 1]);
	block->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	block->setScale(irr::core::vector3df(1, 1, 1));
	block->setPosition(pos);
	if (x >= 0 && x < 11 && y >= 0 && y < 11)
		_blocks.push_back(block);
	initBackBlock(10 * x - 55, 55 - 10 * y);
}

void	Gui::initBackBlock(int x, int y)
{
	const irr::core::vector3df	pos(x, y, 10);
	irr::scene::ISceneNode		*block;

	block = _smgr->addCubeSceneNode();
	if (block == nullptr)
		throw Exception("Back block not created");
	block->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	block->setScale(irr::core::vector3df(1, 1, 0.01));
	block->setPosition(pos);
	block->setMaterialTexture(0, _gameBlocks[MAP_TYPE_EMPTY + 1]);
}

void	Gui::destroyAll(void)
{
	if (!_resetGame)
		_parser.saveMap(_map);
	_parser.setSound(_sounds);
	_device->drop();
}

void	Gui::handleKeys(bool index)
{
	Player::g_actions[index] = ACTION_NONE;
	if (_receiver->IsKeyDown(_key[index].up))
		Player::g_actions[index] = ACTION_MOVE_UP;
        if (_receiver->IsKeyDown(_key[index].right))
		Player::g_actions[index] = ACTION_MOVE_RIGHT;
	if (_receiver->IsKeyDown(_key[index].left))
		Player::g_actions[index] = ACTION_MOVE_LEFT;
	if (_receiver->IsKeyDown(_key[index].down))
		Player::g_actions[index] = ACTION_MOVE_DOWN;
	if (_receiver->IsKeyDown(_key[index].drop))
		Player::g_actions[index] = ACTION_PLACE_BOMB;
}

/*
**Ajout des différents boutons avec texture.
*/
void 	Gui::addPlayButton(void)
{
	irr::gui::IGUIButton	*playButton;
	std::wstring		btnName;
	irr::video::ITexture	*button;
	irr::video::ITexture	*button_pressed;

	if (_resetGame)
		btnName = L"New Game";
	else
		btnName = L"Resume Game";
	playButton = _guienv->addButton(irr::core::rect<irr::s32>
		(BUTTON_REF_SIZE_X/2 - BUTTON_REF_SIZE_Y/2, 200 + 50, BUTTON_REF_SIZE_X/2 + BUTTON_REF_SIZE_Y/2, 50 + 200 + 92), 0,
		EventReceiver::GUI_ID_PLAY_BUTTON, btnName.c_str());
	button = _load.getTexture("gui/Button_normal.png");
	button_pressed = _load.getTexture("gui/Button_pressed.png");
	playButton->setOverrideFont(_font);
	playButton->setImage(button);
	playButton->setPressedImage(button_pressed);
	playButton->setScaleImage(true);
}

void	Gui::addResetButton(void)
{
	irr::gui::IGUIButton	*resetBtn;
	irr::video::ITexture 	*button;
	irr::video::ITexture	*button_pressed;

	resetBtn = _guienv->addButton(irr::core::rect<irr::s32>
		(BUTTON_REF_SIZE_X/2 - 550, 250, BUTTON_REF_SIZE_X/2 - 350, 50 + 200 + 92), 0,
		EventReceiver::GUI_ID_RESET_BUTTON, L"Reset");
	button = _load.getTexture("gui/Button_normal.png");
	button_pressed = _load.getTexture("gui/Button_pressed.png");
	resetBtn->setOverrideFont(_font);
	resetBtn->setImage(button);
	resetBtn->setPressedImage(button_pressed);
	resetBtn->setScaleImage(true);
}

void 	Gui::addPlayerButton(void)
{
	irr::gui::IGUIButton *oneButton = _guienv->addButton(irr::core::rect<irr::s32>
		(450, 250, 500, 330), 0,
		EventReceiver::GUI_ID_ONE_BUTTON, L"");
	irr::gui::IGUIButton *twoButton = _guienv->addButton(irr::core::rect<irr::s32>
		(550, 250, 600, 330), 0,
		EventReceiver::GUI_ID_TWO_BUTTON, L"");
	oneButton->setDrawBorder(0);
	oneButton->setUseAlphaChannel(true);
	twoButton->setDrawBorder(0);
	twoButton->setUseAlphaChannel(true);
}
void 	Gui::addLoadButton(void)
{
	irr::gui::IGUIButton *loadButton = _guienv->addButton(irr::core::rect<irr::s32>
		(BUTTON_REF_SIZE_X/2 - BUTTON_REF_SIZE_Y/2, 200 + 200, BUTTON_REF_SIZE_X/2 + BUTTON_REF_SIZE_Y/2, 200 + 200 + 92), 0,
		EventReceiver::GUI_ID_LOAD_BUTTON, L"Load Game");
	irr::video::ITexture *Button = _load.getTexture("gui/Button_normal.png");
	irr::video::ITexture *Button_pressed = _load.getTexture("gui/Button_pressed.png");
	loadButton->setOverrideFont(_font);
	loadButton->setImage(Button);
	loadButton->setPressedImage(Button_pressed);
	loadButton->setScaleImage(true);
}

void 	Gui::addOptionsButton(void)
{
	irr::gui::IGUIButton *optionsButton = _guienv->addButton(irr::core::rect<irr::s32>
		(BUTTON_REF_SIZE_X/2 - BUTTON_REF_SIZE_Y/2, 350 + 200, BUTTON_REF_SIZE_X/2 + BUTTON_REF_SIZE_Y/2, 350 + 200 + 92), 0,
		EventReceiver::GUI_ID_OPTIONS_BUTTON, L"Options");
	irr::video::ITexture *Button = _load.getTexture("gui/Button_normal.png");
	irr::video::ITexture *Button_pressed = _load.getTexture("gui/Button_pressed.png");
	optionsButton->setOverrideFont(_font);
	optionsButton->setImage(Button);
	optionsButton->setPressedImage(Button_pressed);
	optionsButton->setScaleImage(true);
}

void 	Gui::addCommandsButton(void)
{
	irr::gui::IGUIButton *optionsButton = _guienv->addButton(irr::core::rect<irr::s32>
		(BUTTON_REF_SIZE_X/2 - BUTTON_REF_SIZE_Y/2, 350 + 200, BUTTON_REF_SIZE_X/2 + BUTTON_REF_SIZE_Y/2, 350 + 200 + 92), 0,
		EventReceiver::GUI_ID_COMMANDS_BUTTON, L"Commands");
	irr::video::ITexture *Button = _load.getTexture("gui/Button_normal.png");
	irr::video::ITexture *Button_pressed = _load.getTexture("gui/Button_pressed.png");
	optionsButton->setOverrideFont(_font);
	optionsButton->setImage(Button);
	optionsButton->setPressedImage(Button_pressed);
	optionsButton->setScaleImage(true);
}

void 	Gui::addReturnButton(int id, int decal)
{
	irr::gui::IGUIButton *quitButton = _guienv->addButton(irr::core::rect<irr::s32>
		(BUTTON_REF_SIZE_X/2 - BUTTON_REF_SIZE_Y/2, 500 + 200 + decal, BUTTON_REF_SIZE_X/2 + BUTTON_REF_SIZE_Y/2, 500 + 200 + 92 + decal), 0,
		id, L"Return");
	irr::video::ITexture *Button = _load.getTexture("gui/Button_normal.png");
	irr::video::ITexture *Button_pressed = _load.getTexture("gui/Button_pressed.png");
	quitButton->setOverrideFont(_font);
	quitButton->setImage(Button);
	quitButton->setPressedImage(Button_pressed);
	quitButton->setScaleImage(true);
}

void 	Gui::addQuitButton(void)
{
	irr::gui::IGUIButton *quitButton = _guienv->addButton(irr::core::rect<irr::s32>
		(BUTTON_REF_SIZE_X/2 - BUTTON_REF_SIZE_Y/2, 500 + 200, BUTTON_REF_SIZE_X/2 + BUTTON_REF_SIZE_Y/2, 500 + 200 + 92), 0,
		EventReceiver::GUI_ID_QUIT_BUTTON, L"Quit");
	irr::video::ITexture *Button = _load.getTexture("gui/Button_normal.png");
	irr::video::ITexture *Button_pressed = _load.getTexture("gui/Button_pressed.png");
	quitButton->setOverrideFont(_font);
	quitButton->setImage(Button);
	quitButton->setPressedImage(Button_pressed);
	quitButton->setScaleImage(true);
}

void 	Gui::setPlayerHandler(bool duo)
{
	if (!duo){
		_guienv->addImage(_load.getTexture("gui/one.png"),
			irr::core::position2d<int>(450, 250));
		_guienv->addImage(_load.getTexture("gui/two_off.png"),
			irr::core::position2d<int>(550, 250));
	} else {
		_guienv->addImage(_load.getTexture("gui/two.png"),
		irr::core::position2d<int>(550, 250));
		_guienv->addImage(_load.getTexture("gui/one_off.png"),
		irr::core::position2d<int>(450, 250));
	}
	addPlayerButton();
	_duo = duo;
}

/*
** Gestions du volume, affichage des sprites et gestions des boutons.
*/
void 	Gui::setVolumeHandler(void)
{
	_guienv->addImage(_load.getTexture("gui/Music.png"),
			irr::core::position2d<int>(570, 350));
	_guienv->addImage(_load.getTexture("gui/Effect.png"),
			irr::core::position2d<int>(570, 450));
	displayVolumeMusic(0);
	displayVolumeEffect(0);
}

void	Gui::setGameOff(void) noexcept
{
	_game = false;
}

/*
** Initialisation des vectors pour la positions et les sprites du volume
*/
void 	Gui::initPosVector(std::vector<int> &pos)
{
	pos.push_back(52);
	pos.push_back(37);
	pos.push_back(22);
	pos.push_back(10);
	pos.push_back(0);
}

void 	Gui::initPathVector(std::vector<irr::io::path> &sprite)
{
	sprite.push_back("gui/volume_1.png");
	sprite.push_back("gui/volume_2.png");
	sprite.push_back("gui/volume_3.png");
	sprite.push_back("gui/volume_4.png");
	sprite.push_back("gui/volume_5.png");
}


void 	Gui::displayVolumeSprite(int decal)
{
	_guienv->addImage(_load.getTexture("gui/volume_off_1.png"),
	irr::core::position2d<int>(1020, 330 + 67 - 15 + decal));
	_guienv->addImage(_load.getTexture("gui/volume_off_2.png"),
	irr::core::position2d<int>(1060, 330 + 67 - 30 + decal));
	_guienv->addImage(_load.getTexture("gui/volume_off_3.png"),
	irr::core::position2d<int>(1100, 330 + 67 - 45 + decal));
	_guienv->addImage(_load.getTexture("gui/volume_off_4.png"),
	irr::core::position2d<int>(1140, 330 + 67 - 57 + decal));
	_guienv->addImage(_load.getTexture("gui/volume_off_5.png"),
	irr::core::position2d<int>(1180, 330 + decal));
}
void 	Gui::displayVolumeMusic(int change)
{
	int ite = 0;
	int  posX = 1020;
	std::vector<int> pos;
	std::vector<irr::io::path> sprite;
	initPosVector(pos);
	initPathVector(sprite);
	_sounds.music += change;
	if (_sounds.music < 0)
		_sounds.music = 0;
	if (_sounds.music > 5)
		_sounds.music = 5;
	Mixer::mixer.adjustMusicsVolume(_sounds.music);
	displayVolumeSprite(0);
	while (ite < _sounds.music) {
		_guienv->addImage(_load.getTexture(sprite[ite].c_str()),
		irr::core::position2d<int>(posX, 330 + pos[ite]));
		++ite;
		posX += 40;
	}
	addPlusButton(0, EventReceiver::GUI_ID_PLUS_MUSIC_BUTTON);
	addLessButton(0, EventReceiver::GUI_ID_LESS_MUSIC_BUTTON);
}

void 	Gui::displayVolumeEffect(int change)
{
	int ite = 0;
	int  posX = 1020;
	std::vector<int> pos;
	std::vector<irr::io::path> sprite;
	initPosVector(pos);
	initPathVector(sprite);
	_sounds.soundEffect += change;
	if (_sounds.soundEffect < 0)
		_sounds.soundEffect = 0;
	if (_sounds.soundEffect > 5)
		_sounds.soundEffect = 5;
	Mixer::mixer.adjustEffectsVolume(_sounds.soundEffect);
	displayVolumeSprite(100);
	while (ite < _sounds.soundEffect) {
		_guienv->addImage(_load.getTexture(sprite[ite].c_str()),
		irr::core::position2d<int>(posX, 430 + pos[ite]));
		++ite;
		posX += 40;
	}
	addPlusButton(100, EventReceiver::GUI_ID_PLUS_EFFECT_BUTTON);
	addLessButton(100, EventReceiver::GUI_ID_LESS_EFFECT_BUTTON);
}

void 	Gui::addPlusButton(int decal, int id)
{
	irr::gui::IGUIButton *plusButton = _guienv->addButton(irr::core::rect<irr::s32>
		(1220, 350 + decal, 1320, 410 + decal), 0,
		id);
	irr::video::ITexture *Button = _load.getTexture("gui/plus.png");
	irr::video::ITexture *Button_pressed = _load.getTexture("gui/plus_pressed.png");
	plusButton->setImage(Button);
	plusButton->setPressedImage(Button_pressed);
	plusButton->setUseAlphaChannel(true);
	plusButton->setDrawBorder(0);
	plusButton->setScaleImage(true);
}

void 	Gui::addLessButton(int decal, int id)
{
	irr::gui::IGUIButton *lessButton = _guienv->addButton(irr::core::rect<irr::s32>
		(920, 365 + decal, 1020, 390 + decal), 0,
		id);
	irr::video::ITexture *Button = _load.getTexture("gui/less.png");
	irr::video::ITexture *Button_pressed = _load.getTexture("gui/less_pressed.png");
	lessButton->setImage(Button);
	lessButton->setPressedImage(Button_pressed);
	lessButton->setUseAlphaChannel(true);
	lessButton->setScaleImage(true);
	lessButton->setDrawBorder(0);
}

/*
** Getter for the volume level setup in the menu.
** The value is between 0 (mute) and 5 (max).
*/
int	Gui::getVolumeMusic(void) const
{
	return this->_sounds.music;
}

int	Gui::getVolumeEffect(void) const
{
	return this->_sounds.soundEffect;
}
