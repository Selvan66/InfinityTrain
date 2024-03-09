/** @file MusicPlayer.h */
#pragma once
#include <array>
#include <string>

#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

class MusicPlayer : public sf::NonCopyable {
public:
  enum MusicsID { Menu, Game, MusicsCount, None };

public:
  MusicPlayer();
  void play(MusicsID id);
  void stop();
  void setPaused(bool paused);
  void setVolume(float volume);
  void replay();

private:
  sf::Music mMusic;
  MusicsID mPlayedMusic;
  std::array<std::string, MusicsCount> mFilenames;
  float mVolume;
};