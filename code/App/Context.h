/** @file Context.h */
#pragma once

#include "Utils/ResourceIdentifiers.h"
#include "Effects/SoundPlayer.h"

struct Context : public sf::NonCopyable
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
	SoundPlayer sounds;
};