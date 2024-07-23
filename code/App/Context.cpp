/** @file Context.cpp */
#include "spdlog/spdlog.h"

#include "Context.h"

Context::Context()
  : window(), textures(), fonts(), sounds(), musics(), player(*this),
    settings(), statistics() {
  textures.load(TexturesID::Icon, "image/icon.png");

  applyGraphicSettings();
  applyContolSettings();
  applyAudioSettings();
}

void Context::applyGraphicSettings() {
  std::pair<unsigned int, unsigned int> window_size =
    settings.get<std::pair<unsigned int, unsigned int>>("Graphics",
                                                        "Resolution");
  bool fullscreen = settings.get<bool>("Graphics", "Fullscreen");
  if (fullscreen) {
    window.create(sf::VideoMode(1920, 1080), "Infinity Train",
                  sf::Style::Fullscreen);
  } else {
    window.create(sf::VideoMode(1920, 1080), "Infinity Train",
                  sf::Style::Close);
    window.setSize(sf::Vector2u(window_size.first, window_size.second));
  }
  unsigned int screen_width = sf::VideoMode::getDesktopMode().width;
  unsigned int screen_height = sf::VideoMode::getDesktopMode().height;
  window.setPosition({static_cast<int>(screen_width) / 2 -
                        static_cast<int>(window_size.first) / 2,
                      static_cast<int>(screen_height) / 2 -
                        static_cast<int>(window_size.second) / 2});
  window.setKeyRepeatEnabled(false);
  window.setVerticalSyncEnabled(true);
  auto icon = textures.get(TexturesID::Icon).copyToImage();
  window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
  spdlog::info("Context::applyGraphicSettings");
}

void Context::applyAudioSettings() {
  float sound_volume = settings.get<float>("Audio", "Sounds Volume");
  sounds.setVolume(sound_volume);
  float music_volume = settings.get<float>("Audio", "Music Volume");
  musics.setVolume(music_volume);
  spdlog::info("Context::applyAudioSettings");
}

void Context::applyContolSettings() {
  player.loadPlayerInput();
  spdlog::info("Context::applyContolSettings");
}
