//
// EPITECH PROJECT, 2018
// INDIE_STUDIO
// File description:
// 	Mixer
//

#include "Mixer.hpp"
#include "Sound.hpp"
#include "Exception.hpp"

/*
** Allows the mixer to be called anywhere it needed.
*/
Mixer	Mixer::mixer;

/*
** Ctor / Dtor
*/
Mixer::Mixer(void) : _engine(nullptr)
{
}

Mixer::~Mixer()
{
	this->_engine->drop();
}

/*
** Mixer settings
*/
void	Mixer::initializeMixer(const std::string &prefixPath,
	const Sound_t &volume)
{
	this->_prefixPath = prefixPath;
	this->_engine = irrklang::createIrrKlangDevice();
	if (!this->_engine) {
		throw Exception("Can't create sound engine");
	}
	this->createSoundObjects();
	this->setSoundObjectsEngine();
	this->setSoundObjectsPaths();
	this->setSoundObjectsType();
	this->adjustMusicsVolume(volume.music);
	this->adjustEffectsVolume(volume.soundEffect);
}

/*
** Set the volume of the musics.
** The level provided is an int between 0 and 5 (set from the menu).
** The volume handler of IrrKlang needs a float between 0 and 1.
** So, level needs to be converted.
** New volume is applied to all playing musics.
*/
void		Mixer::adjustMusicsVolume(int level)
{
	float	convertedLevel = static_cast<float>(level) / 5;

	this->_musicMenu.changeVolume(convertedLevel);
	this->_musicGame.changeVolume(convertedLevel);
}

/*
** Set the volume of the effects.
** The level provided is an int between 0 and 5 (set from the menu).
** The volume handler of IrrKlang needs a float between 0 and 1.
** So, level needs to be converted.
*/
void		Mixer::adjustEffectsVolume(int level)
{
	float	convertedLevel = static_cast<float>(level) / 5;

	this->_effectClick.changeVolume(convertedLevel);
	this->_effectDropBomb.changeVolume(convertedLevel);
	this->_effectGrabBoost.changeVolume(convertedLevel);
	this->_effectDie.changeVolume(convertedLevel);
	this->_effectWin.changeVolume(convertedLevel);
	this->_effectLose.changeVolume(convertedLevel);
	this->_effectExplosion.changeVolume(convertedLevel);
}

/*
** Following methods play the corresponding sound.
*/
void	Mixer::playMusicMenu(void)
{
	this->playMusic(this->_musicMenu);
}

void	Mixer::playMusicGame(void)
{
	this->playMusic(this->_musicGame);
}

void	Mixer::playEffectClick(void)
{
	this->playEffect(this->_effectClick);
}

void	Mixer::playEffectDropBomb(void)
{
	this->playEffect(this->_effectDropBomb);
}

void	Mixer::playEffectGrabBoost(void)
{
	this->playEffect(this->_effectGrabBoost);
}

void	Mixer::playEffectDie(void)
{
	this->playEffect(this->_effectDie);
}

void	Mixer::playEffectWin(void)
{
	this->playEffect(this->_effectWin);
}

void	Mixer::playEffectLose(void)
{
	this->playEffect(this->_effectLose);
}

void	Mixer::playEffectExplosion(void)
{
	this->playEffect(this->_effectExplosion);
}

/*
** Private methods.
*/
/*
** Manages the creation of all sounds.
*/
void 	Mixer::createSoundObjects(void)
{
	this->_musicMenu = Sound();
	this->_musicGame = Sound();
	this->_effectClick = Sound();
	this->_effectDropBomb = Sound();
	this->_effectGrabBoost = Sound();
	this->_effectDie = Sound();
	this->_effectWin = Sound();
	this->_effectLose = Sound();
	this->_effectExplosion = Sound();
}

/*
** Provides a sound engine to the created sounds.
*/
void	Mixer::setSoundObjectsEngine(void)
{
	this->_musicMenu.setSoundEngine(this->_engine);
	this->_musicGame.setSoundEngine(this->_engine);
	this->_effectClick.setSoundEngine(this->_engine);
	this->_effectDropBomb.setSoundEngine(this->_engine);
	this->_effectGrabBoost.setSoundEngine(this->_engine);
	this->_effectDie.setSoundEngine(this->_engine);
	this->_effectWin.setSoundEngine(this->_engine);
	this->_effectLose.setSoundEngine(this->_engine);
	this->_effectExplosion.setSoundEngine(this->_engine);
}

/*
** Provides the paths to the corresponding sounds to load.
*/
void	Mixer::setSoundObjectsPaths(void)
{
	this->_musicMenu.setTrackPath(_prefixPath +
		"Sounds/Musics/Bit_Shift.ogg");
	this->_musicGame.setTrackPath(_prefixPath +
		"Sounds/Musics/Overworld.ogg");
	this->_effectClick.setTrackPath(_prefixPath +
		"Sounds/Effects/click.ogg");
	this->_effectDropBomb.setTrackPath(_prefixPath +
		"Sounds/Effects/drop_bomb.ogg");
	this->_effectGrabBoost.setTrackPath(_prefixPath +
		"Sounds/Effects/grab_boost.ogg");
	this->_effectDie.setTrackPath(_prefixPath +
		"Sounds/Effects/death2.ogg");
	this->_effectWin.setTrackPath(_prefixPath +
		"Sounds/Effects/win.ogg");
	this->_effectLose.setTrackPath(_prefixPath +
		"Sounds/Effects/lose.ogg");
	this->_effectExplosion.setTrackPath(_prefixPath +
		"Sounds/Effects/explosion2.ogg");
}

/*
** Indicates if sound is a music (to be play in loop) or an effect (play once).
*/
void	Mixer::setSoundObjectsType(void)
{
	this->_musicMenu.setSoundType(0);
	this->_musicGame.setSoundType(0);
	this->_effectClick.setSoundType(1);
	this->_effectDropBomb.setSoundType(1);
	this->_effectGrabBoost.setSoundType(1);
	this->_effectDie.setSoundType(1);
	this->_effectWin.setSoundType(1);
	this->_effectLose.setSoundType(1);
	this->_effectExplosion.setSoundType(1);
}

/*
** Play the music passed as parameter.
** If another music is playing, then stop it first.
*/
void	Mixer::playMusic(Sound &music)
{
	if (&music !=  &_musicMenu && this->_musicMenu.isPlaying()) {
		this->_musicMenu.stopTrack();
	}
	if (&music != &_musicGame && this->_musicGame.isPlaying()) {
		this->_musicGame.stopTrack();
	}
	if (music.isPlaying() == false) {
		music.playTrack();
	}
}

/*
** Play the effect passed as parameter.
** If this effect is playing, then stop it first (no need to stop the others).
*/
void	Mixer::playEffect(Sound &effect)
{
	if (effect.isPlaying()) {
		effect.stopTrack();
	}
	effect.playTrack();
}
