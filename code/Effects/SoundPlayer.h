/** @file SoundPlayer.h */
#pragma once

#include <list>

#include "Utils/ResourceIdentifiers.h"

class SoundPlayer : public sf::NonCopyable {
public:
  SoundPlayer();
  void play(SoundsID sound);
  void play(SoundsID sound, sf::Vector2f position);
  void removeStoppedSounds();
  void setListenerPosition(sf::Vector2f position);
  void setVolume(float volume);

private:
  void loadSounds();

private:
  SoundBufferHolder mSoundBuffer;
  std::list<sf::Sound> mSounds;
  float mVolume;

  const float ListenerZ;
  const float Attenuation;
  const float MinDistance2D;
  const float MinDistance3D;
};