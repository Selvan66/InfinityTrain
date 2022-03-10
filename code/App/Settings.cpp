/** @file Settings.cpp */
#include <fstream>
#include <iostream>

#include "SFML/Window.hpp"

#include "App/Settings.h"

Settings::Settings()
: mSettings()
{
    load();    
}

Settings::~Settings()
{
    save();
}

void Settings::save()
{
    std::ofstream o("settings.json");
    if (o.is_open())
    {
        o << mSettings; 
    }
    else
    {
        std::cerr << "Cannot save" << std::endl;
    }
}

void Settings::load()
{
    std::ifstream i("settings.json");
    if (i.is_open())
    {
        i >> mSettings;
    }
    else
    {
        mSettings["Graphics"]["Window Size"] = std::pair<int, int>(1024, 768);
        mSettings["Graphics"]["Fullscreen"] = false;

        mSettings["Control"]["Up"] = "W";
        mSettings["Control"]["Down"] = "S";
        mSettings["Control"]["Left"] = "A";
        mSettings["Control"]["Right"] = "D";
        mSettings["Control"]["Shot"] = "Mleft";
        mSettings["Control"]["Special"] = "Space";

        mSettings["Audio"]["Music Volume"] = 100;
        mSettings["Audio"]["Sounds Volume"] = 100;
    }
}