//
// EPITECH PROJECT, 2018
// INDIE_STUDIO
// File description:
// 	Sound
//

#include <iostream>

#include "../../inc/Sound.hpp"
#include "../../inc/Exception.hpp"

/*
** Sound object creator.
** Initialzes the sound engine and stores the path to the track to be played.
*/
Sound::Sound()
:
_soundEngine(nullptr), _track(nullptr), _trackPath(""),
_isPlaying(false), _soundType(0)
{
}

/*
** Sound object destructor.
** Destroy the sound engine.
*/
Sound::~Sound(void)
{
}

/*
** Setters.
*/
void	Sound::setSoundEngine(irrklang::ISoundEngine *se)
{
	this->_soundEngine = se;
}

void	Sound::setTrackPath(std::string trackPath)
{
	this->_trackPath = trackPath;
}

void	Sound::setSoundType(short soundType)
{
	this->_soundType = soundType;
}
/*
** Methods.
*/
/*
** Sound start.
** Launches the play of the track.
** If sound if an effect, then don't play it in loop. Else, loop on it.
** PROTO play2D :
** virtual ISound* irrklang::ISoundEngine::play2D(
**		const char *soundFileName,
**		bool playLooped = false,
**		bool startPaused = false,
**		bool track = false,
**		E_STREAM_MODE streamMode = ESM_AUTO_DETECT,
**		bool enableSoundEffects = false);
** ! : if none of start_paused, looped or track are set to true, then play2D
** doesn't return an ISound pointer (so _track will stay set at nullptr) !
*/
void	Sound::playTrack(void)
{
	if (this->isAnEffect() == true) {
		this->_track = this->_soundEngine->play2D(
			this->_trackPath.c_str(), false, false, true);
	} else {
		this->_track = this->_soundEngine->play2D(
			this->_trackPath.c_str(), true, false, true);
	}
	this->_track->setVolume(this->_volume);
	if (_track == nullptr) {
		std::cerr << "! : Cannot play sound : " + this->_trackPath <<
		std::endl;
		this->_isPlaying = false;
	} else {
		this->_isPlaying = true;
	}
}

/*
** Sound stop.
** Stops the play of the tracks and destroys it.
*/
void	Sound::stopTrack(void)
{
	this->_track->stop();
	this->_track->drop();
	this->_track = nullptr;
	this->_isPlaying = false;
}

/*
** Play indicator.
** Returns true if the track is playing, false otherwise.
*/
bool	Sound::isPlaying(void)
{
	return this->_isPlaying;
}

bool	Sound::isAnEffect(void)
{
	return this->_soundType == 1 ? true : false;
}

/*
** Volume setter.
** Sets the track's volume at the given level.
*/
void	Sound::changeVolume(float level)
{
	if (this->_track && this->isPlaying()) {
		this->_volume = static_cast<irrklang::ik_f32>(level);
		this->_track->setVolume(this->_volume);
	}
	else {
		this->_volume = static_cast<irrklang::ik_f32>(level);
	}
}
