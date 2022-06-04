/** @file Context.h */
#pragma once

#include "Effects/SoundPlayer.h"
#include "Effects/MusicPlayer.h"
#include "App/Settings.h"
#include "App/Statistics.h"
#include "Player/Player.h"

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
	MusicPlayer musics;
	Player player;
	Settings settings;
	Statistics statistics;
};