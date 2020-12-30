//
// EPITECH PROJECT, 2018
// INDIE_STUDIO
// File description:
// 	Sounds
//

#ifndef SOUND_HPP_
	#define SOUND_HPP_

	#include <irrKlang.h>
	#include <string>

	/*
	** Instanciate a sound object.
	** Must create a new instance of this class for each sound used.
	** Provides some encapsultaion of IrrKlang library.
	*/
	class Sound {
	public:
		// Ctor & Dtor
		Sound(void);
		~Sound(void);
		// Setters
		void			setSoundEngine(
			irrklang::ISoundEngine *se);
		void 			setTrackPath(std::string trackPath);
		void			setSoundType(short type);
		// Player
		void			playTrack(void);
		void			stopTrack(void);
		bool			isPlaying(void);
		bool			isAnEffect(void);
		void			changeVolume(float level);
	private:
		irrklang::ISoundEngine	*_soundEngine;
		irrklang::ISound	*_track;
		std::string		_trackPath;
		bool			_isPlaying;
		short			_soundType;
		irrklang::ik_f32	_volume;
	};

#endif /* !SOUND_HPP_ */
