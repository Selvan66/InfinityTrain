/** @file StartLevel.h */
#pragma once

#include "Objects/Levels/Level.h"

class StartLevel : public Level
{
    public:
        StartLevel(Context& context, PlayerInfo& playerInfo, unsigned int numLevel);

        virtual LevelID::ID nextLevel() const;
    private:
        void buildScene();
};