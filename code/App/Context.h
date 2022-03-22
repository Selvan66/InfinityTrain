/** @file Context.h */
#pragma once

#include "Effects/SoundPlayer.h"
#include "App/Settings.h"
#include "App/Statistics.h"
#include "App/Player.h"

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
	Player player;
	Settings settings;
	Statistics statistics;
};