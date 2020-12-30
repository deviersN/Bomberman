//
// EPITECH PROJECT, 2018
// indie
// File description:
// Event Receiver
//

#include <iostream>
#include <irrlicht.h>
#include "EventReceiver.hpp"
#include "Gui.hpp"
#include "Mixer.hpp"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

EventReceiver::EventReceiver(irr::IrrlichtDevice *device, Gui *gui):
_device(device), _gui(gui)
{
	for (irr::u32 i=0; i < irr::KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;
}

EventReceiver::~EventReceiver(void)
{

}

// Methods
bool	EventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const
{
	return KeyIsDown[keyCode];
}

bool EventReceiver::OnEvent(const irr::SEvent &event)
{
	if (event.EventType == irr::EET_GUI_EVENT) {
		irr::s32 id = event.GUIEvent.Caller->getID();
		irr::gui::IGUIEnvironment* env = _device->getGUIEnvironment();
		switch(event.GUIEvent.EventType) {
			case irr::gui::EGET_BUTTON_CLICKED:
				Mixer::mixer.playEffectClick();
				return handleButton(id);
			case irr::gui::EGET_FILE_SELECTED:
				return handleFileSelected(event);
		}
	} else if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
		handleEscaping(event.KeyInput);
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	}
	return false;
}

// Private Methods
bool	EventReceiver::handleButton(irr::s32 id)
{
	switch(id) {
		case GUI_ID_QUIT_BUTTON:
			_device->closeDevice();
			return true;
		case GUI_ID_PLAY_BUTTON:
			_gui->displayGame();
			return true;
		case GUI_ID_LOAD_BUTTON:
			_gui->loadMap();
			return true;
		case GUI_ID_OPTIONS_BUTTON:
			_gui->displayOptions();
			return true;
		case GUI_ID_RETURN_BUTTON:
			_gui->displayMenu();
			return true;
		case GUI_ID_RETURN_OPT_BUTTON:
			_gui->displayOptions();
			return true;
		case GUI_ID_RETURN_WINNER:
			_gui->setGameOff();
			return true;
		case GUI_ID_PLUS_MUSIC_BUTTON:
			_gui->displayVolumeMusic(1);
			return true;
		case GUI_ID_LESS_MUSIC_BUTTON:
			_gui->displayVolumeMusic(-1);
			return true;
		case GUI_ID_PLUS_EFFECT_BUTTON:
			_gui->displayVolumeEffect(1);
			return true;
		case GUI_ID_LESS_EFFECT_BUTTON:
			_gui->displayVolumeEffect(-1);
			return true;
		case GUI_ID_COMMANDS_BUTTON:
			_gui->displayButtonMenu();
			return true;
		case GUI_ID_ONE_BUTTON:
			_gui->setPlayerHandler(false);
			return true;
		case GUI_ID_TWO_BUTTON:
			_gui->setPlayerHandler(true);
			return true;
		case GUI_ID_RESET_BUTTON:
			_gui->resetGame();
			return true;
	}
	return false;
}

void	EventReceiver::handleEscaping(const irr::SEvent::SKeyInput &inp)
{
	if (inp.Key != irr::KEY_ESCAPE)
		return;
	if (!inp.PressedDown) {
		_escaping = false;
	} else {
		if (!_escaping)
			_gui->escape(inp.Shift);
		_escaping = true;
	}
}

bool	EventReceiver::handleFileSelected(const irr::SEvent &event)
{
	auto				caller = event.GUIEvent.Caller;
	irr::gui::IGUIFileOpenDialog	*dialog;
	std::wstring			path;

	dialog = static_cast<irr::gui::IGUIFileOpenDialog*>(caller);
	path = std::wstring(dialog->getFileName());
	_gui->loadGame(path);
	return true;	
}
