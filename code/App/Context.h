/** @file Context.h */
#pragma once

#include "Effects/SoundPlayer.h"
#include "App/Settings.h"

struct Context : public sf::NonCopyable
{
	Context();
	void applySettings();

	sf::RenderWindow window;
	TextureHolder textures;
	FontHolder fonts;
	SoundPlayer sounds;
	Settings settings;
};