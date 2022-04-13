/** @file Map.h */
#pragma once

#include "App/Context.h"
#include "Objects/Levels/Level.h"

class Map
{
    public:
        Map(Context& context, Player& player);
        void update(sf::Time dt);
        void draw();
    private:
        Player& mPlayer;
        Level::Ptr mLevel;
        unsigned int mNumLevel;
};