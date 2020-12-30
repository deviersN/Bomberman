//
// EPITECH PROJECT, 2018
// indie
// File description:
// Event Receiver
//

#ifndef EVENTRECEIVER_HPP
	#define EVENTRECEIVER_HPP

	class EventReceiver;

	#include <cstdint>
	#include <irrlicht.h>
	#include "Gui.hpp"

	class EventReceiver: public irr::IEventReceiver {
	public:
		enum GUI_ID
		{
			GUI_ID_QUIT_BUTTON = 101,
			GUI_ID_PLAY_BUTTON,
			GUI_ID_LOAD_BUTTON,
			GUI_ID_OPTIONS_BUTTON,
			GUI_ID_RETURN_BUTTON,
			GUI_ID_RETURN_OPT_BUTTON,
			GUI_ID_RETURN_WINNER,
			GUI_ID_PLUS_MUSIC_BUTTON,
			GUI_ID_LESS_MUSIC_BUTTON,
			GUI_ID_PLUS_EFFECT_BUTTON,
			GUI_ID_LESS_EFFECT_BUTTON,
			GUI_ID_COMMANDS_BUTTON,
			GUI_ID_ONE_BUTTON,
			GUI_ID_TWO_BUTTON,
			GUI_ID_RESET_BUTTON,
		};
		// Ctor Dtor
		EventReceiver(irr::IrrlichtDevice *device, Gui *gui);
		~EventReceiver(void);
		// Getters
		// Setters
		// Methods
		virtual bool OnEvent(const irr::SEvent &event);
		virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;
	private:
		// Private Methods
		bool	handleButton(irr::s32 id);
		void	handleEscaping(const irr::SEvent::SKeyInput &inp);
		bool	handleFileSelected(const irr::SEvent &event);
		// Attributs
		irr::IrrlichtDevice	*_device;
		Gui 			*_gui;
		bool		KeyIsDown[irr::KEY_KEY_CODES_COUNT];
		bool		_escaping = false;
	};

#endif /* !EVENTRECEIVER_HPP */
