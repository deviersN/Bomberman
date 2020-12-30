//
// EPITECH PROJECT, 2018
// INDIE_STUDIO
// File description:
// 	Mixer
//

#ifndef MIXER_HPP_
	#define MIXER_HPP_

	#include <irrKlang.h>
	#include <vector>
	#include "Sound.hpp"
	#include "Loader.hpp"
	#include "Structure.hpp"

	/*
	** Sound mixer.
	** Contains all sounds to be play during the game.
	*/
	class Mixer {
	public:
		static Mixer		mixer;
		// Ctor & Dtor
		Mixer(void);
		~Mixer(void);
		// Mixer settings
		void			initializeMixer(
			const std::string &prefixPath, const Sound_t &volume);
		void			adjustMusicsVolume(int level);
		void			adjustEffectsVolume(int level);
		// Play
		void			playMusicMenu(void);
		void			playMusicGame(void);
		void			playEffectClick(void);
		void			playEffectDropBomb(void);
		void			playEffectGrabBoost(void);
		void			playEffectDie(void);
		void			playEffectWin(void);
		void			playEffectLose(void);
		void			playEffectExplosion(void);
	private:
		// Mixer settings
		void 			createSoundObjects(void);
		void			setSoundObjectsEngine(void);
		void			setSoundObjectsPaths(void);
		void			setSoundObjectsType(void);
		// Play
		void			playMusic(Sound	&music);
		void			playEffect(Sound &effect);
		// Attributs
		std::string		_prefixPath;
		irrklang::ISoundEngine	*_engine;
		Sound			_musicMenu;
		Sound			_musicGame;
		Sound			_effectClick;
		Sound			_effectDropBomb;
		Sound			_effectGrabBoost;
		Sound			_effectDie;
		Sound			_effectWin;
		Sound			_effectLose;
		Sound			_effectExplosion;
	};

#endif /* !MIXER_HPP_ */
