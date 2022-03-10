/** @file Context.h */
#pragma once

#include "Utils/ResourceIdentifiers.h"
#include "Effects/SoundPlayer.h"
#include "App/Settings.h"

struct Context : public sf::NonCopyable
{
	Context()
	: window()
	, textures()
	, fonts()
	, sounds()
	, settings()
	{
		std::pair<int, int> window_size = settings.get<std::pair<int, int>>("Graphics", "Window Size");
		bool fullscreen = settings.get<bool>("Graphics", "Fullscreen");
		if (fullscreen)
		{
			window.create(sf::VideoMode(1920, 1080), "Infinity Train", sf::Style::Fullscreen);
		}
		else
		{
			window.create(sf::VideoMode(1920, 1080), "Infinity Train", sf::Style::Close);
			window.setSize(sf::Vector2u(window_size.first, window_size.second));
		}
		
	}

	sf::RenderWindow window;
	TextureHolder textures;
	FontHolder fonts;
	SoundPlayer sounds;
	Settings settings;
};