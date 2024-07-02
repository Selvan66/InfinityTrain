/** @file ResourceIdentifiers.h */
#pragma once

#include <SFML/Audio.hpp>

#include "Utils/ParserGui.h"
#include "Utils/ResourceHolder.h"

enum class TexturesID {
  TitleScreen,
  Gui,
  Icon,
  Loading,
  DefaultLevel,
  PrehistoryLevel,
  StartLevel,
  FirstLevel,
  Player,
  Money,
  Heart,
  Potion,
  Door,
  HeadArmor,
  ChestArmor,
  HeavyBoots,
  LightBoots,
  Knife,
  Sword,
  Weapons,
  Arrow,
  Bazooka,
  Rocket,
  Dog,
};

typedef ResourceHolder<sf::Texture, TexturesID> TextureHolder;

enum class FontsID { PixelFont };

typedef ResourceHolder<sf::Font, FontsID> FontHolder;

enum class SoundsID { ButtonHover, ButtonClick };

typedef ResourceHolder<sf::SoundBuffer, SoundsID> SoundBufferHolder;

enum class GuiFileID {
  MenuOptions,
  AudioSetting,
  GraphicsSetting,
  Pause,
  GameOver,
  Setting,
  Statistics,
  ControlSetting,
  Stats,
  Map,
  About,
};

typedef ResourceHolder<ParserGui, GuiFileID> GuiFileHolder;
