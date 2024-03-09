/** @file Settings.cpp */
#include <fstream>
#include <iostream>

#include "SFML/Window.hpp"

#include "App/Settings.h"

Settings::Settings() : mSettings() { load(); }

Settings::~Settings() { save(); }

void Settings::save() {
  std::ofstream o("settings.json");
  if (o.is_open())
    o << mSettings;
  else
    std::cerr << "Cannot save settings" << std::endl;
}

void Settings::load() {
  std::ifstream i("settings.json");
  if (i.is_open()) {
    i >> mSettings;
  } else {
    mSettings["Graphics"]["Resolution"] = std::pair<int, int>(1366, 768);
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
  }
}