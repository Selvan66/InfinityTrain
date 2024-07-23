/** @file Settings.cpp */
#include <fstream>

#include "spdlog/spdlog.h"

#include "App/Settings.h"

Settings::Settings() : mSettings() { load(); }

Settings::~Settings() { save(); }

void Settings::save() {
  std::ofstream o("settings.json");
  if (!o.is_open()) {
    spdlog::warn("Settings::save | Cannot save settings");
    return;
  }

  o << mSettings;
  spdlog::info("Settings::save | Settings saved");
}

void Settings::load() {
  std::ifstream i("settings.json");

  if (!i.is_open()) {
    spdlog::warn("Settings::load | Cannot load settings (using default)");
    mSettings["Graphics"]["Resolution"] =
      std::pair<unsigned int, unsigned int>(1366, 768);
    mSettings["Graphics"]["Fullscreen"] = false;

    mSettings["Control"]["Up"] = "W";
    mSettings["Control"]["Down"] = "S";
    mSettings["Control"]["Left"] = "A";
    mSettings["Control"]["Right"] = "D";
    mSettings["Control"]["Fire"] = "Mleft";
    mSettings["Control"]["Special"] = "Space";
    mSettings["Control"]["Interact"] = "E";

    mSettings["Audio"]["Music Volume"] = 100.0f;
    mSettings["Audio"]["Sounds Volume"] = 100.0f;
    return;
  }

  i >> mSettings;
  spdlog::info("Settings::load | Settings loaded");
}
