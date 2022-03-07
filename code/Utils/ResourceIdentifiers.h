/** @file ResourceIdentifiers.h */
#pragma once

#include <SFML/Graphics.hpp>

#include "Utils/ResourceHolder.h"

enum class TexturesID
{
    TitleScreen
};

typedef ResourceHolder<sf::Texture, TexturesID> TextureHolder;

enum class FontsID
{
    PixelFont
};

typedef ResourceHolder<sf::Font, FontsID> FontHolder;
