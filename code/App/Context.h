/** @file Context.h */
#pragma once

#include "Effects/SoundPlayer.h"
#include "App/Settings.h"

struct Context : public sf::NonCopyable
{
	Context();
	void applyGraphicSettings();
	void applyAudioSettings();
	void applyContolSettings();

	sf::RenderWindow window;
	TextureHolder textures;
	FontHolder fonts;
	SoundPlayer sounds;
	Settings settings;
};