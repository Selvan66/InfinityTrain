/** @file ResourceIdentifiers.h */
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Utils/ResourceHolder.h"
#include "Utils/ParserGui.h"

enum class TexturesID
{
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
};

typedef ResourceHolder<sf::Texture, TexturesID> TextureHolder;

enum class FontsID
{
	PixelFont
};

typedef ResourceHolder<sf::Font, FontsID> FontHolder;

enum class SoundsID
{
	ButtonHover,
	ButtonClick
};

typedef ResourceHolder<sf::SoundBuffer, SoundsID> SoundBufferHolder;

enum class GuiFileID
{
	MenuOptions,
	AudioSetting,
	GraphicsSetting,
	Pause,
	Setting,
	Statistics,
	ControlSetting,
	Stats,
	Map,
};

typedef ResourceHolder<ParserGui, GuiFileID> GuiFileHolder;