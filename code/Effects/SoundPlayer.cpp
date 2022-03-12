/** @file SoundPlayer.cpp */
#include "Effects/SoundPlayer.h"


SoundPlayer::SoundPlayer()
: mSoundBuffer()
, mSounds()
, ListenerZ(300.f)
, Attenuation(8.f)
, MinDistance2D(200.f)
, MinDistance3D(std::sqrt(SoundPlayer::MinDistance2D*SoundPlayer::MinDistance2D + SoundPlayer::ListenerZ*SoundPlayer::ListenerZ))
{
    loadSounds();
    sf::Listener::setDirection(0.f, 0.f, -1.f);
}

void SoundPlayer::play(SoundsID sound)
{
    sf::Vector3f position = sf::Listener::getPosition();
    play(sound, sf::Vector2f(position.x, position.y));
}

void SoundPlayer::play(SoundsID sound, sf::Vector2f position)
{
    mSounds.push_back(sf::Sound());
    sf::Sound& playSound = mSounds.back();

    playSound.setBuffer(mSoundBuffer.get(sound));
    playSound.setPosition(position.x, -position.y, 0.0);
    playSound.setAttenuation(Attenuation);
    playSound.setMinDistance(MinDistance3D);
    playSound.setVolume(mVolume);

    playSound.play();
}

void SoundPlayer::removeStoppedSounds()
{
    mSounds.remove_if([] (const sf::Sound& s) {return s.getStatus() == sf::Sound::Stopped; });
}

void SoundPlayer::setListenerPosition(sf::Vector2f position)
{
    sf::Listener::setPosition(position.x, -position.y, ListenerZ);
}

void SoundPlayer::setVolume(float volume)
{
    mVolume = volume;
}

void SoundPlayer::loadSounds()
{
    mSoundBuffer.load(SoundsID::ButtonHover, "sounds/button_hover.wav");
    mSoundBuffer.load(SoundsID::ButtonClick, "sounds/button_click.wav");
}