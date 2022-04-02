/** @file Context.cpp */
#include "Context.h"

Context::Context()
: window()
, textures()
, fonts()
, sounds()
, musics()
, settings()
, statistics()
{
    textures.load(TexturesID::Icon, "image/icon.png");

    applyGraphicSettings();
    applyContolSettings();
    applyAudioSettings();
}

void Context::applyGraphicSettings()
{
    std::pair<int, int> window_size = settings.get<std::pair<int, int>>("Graphics", "Resolution");
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
    window.setKeyRepeatEnabled(false);
   	window.setVerticalSyncEnabled(true);
    auto icon = textures.get(TexturesID::Icon).copyToImage();
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());	
}

void Context::applyAudioSettings()
{
    float sound_volume = settings.get<float>("Audio", "Sounds Volume");
    sounds.setVolume(sound_volume);
    float music_volume = settings.get<float>("Audio", "Music Volume");
    musics.setVolume(music_volume);
}

void Context::applyContolSettings()
{
    
}
