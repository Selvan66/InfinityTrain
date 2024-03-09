/** @file Context.h */
#pragma once

#include "App/Settings.h"
#include "App/Statistics.h"
#include "Effects/MusicPlayer.h"
#include "Effects/SoundPlayer.h"
#include "Player/Player.h"

struct Context : public sf::NonCopyable {
  Context();
  void applyGraphicSettings();
  void applyAudioSettings();
  void applyContolSettings();

  sf::RenderWindow window;
  TextureHolder textures;
  FontHolder fonts;
  GuiFileHolder gui;
  SoundPlayer sounds;
  MusicPlayer musics;
  Player player;
  Settings settings;
  Statistics statistics;
};