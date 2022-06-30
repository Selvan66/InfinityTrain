/** @file ResourceIdentifiers.h */
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Utils/ResourceHolder.h"
#include "Utils/ParserGui.h"

enum class TexturesID
{
	TitleScreen,
	ArrowButtons,
	Checkbox,
	Icon,
	Loading,
	DefaultLevel,
	PrehistoryLevel,
	Player,
	Money,
	Heart
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
};

typedef ResourceHolder<ParserGui, GuiFileID> GuiFileHolder;