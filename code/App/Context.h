/** @file Context.h */
#pragma once

#include "Utils/ResourceIdentifiers.h"

struct Context
{
	Context(sf::VideoMode mode)
	: window(mode, "Infinity Train")
	, textures()
	, fonts()
	, sounds()
	{}

	sf::RenderWindow window;
	TextureHolder textures;
	FontHolder fonts;
	SoundBufferHolder sounds;
};