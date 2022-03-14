/** @file ResourceIdentifiers.h */
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Utils/ResourceHolder.h"

enum class TexturesID
{
	TitleScreen,
	ArrowButtons
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