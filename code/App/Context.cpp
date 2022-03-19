/** @file Context.cpp */
#include "Context.h"

Context::Context()
: window()
, textures()
, fonts()
, sounds()
, settings()
{
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
}

void Context::applyAudioSettings()
{
    float sound_volume = settings.get<float>("Audio", "Sounds Volume");
    sounds.setVolume(sound_volume);
}

void Context::applyContolSettings()
{
    
}
