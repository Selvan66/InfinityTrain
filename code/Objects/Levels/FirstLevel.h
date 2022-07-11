/** @file FirstLevel.h */
#pragma once

#include "Objects/Levels/Level.h"

class FirstLevel : public Level
{
    public:
        FirstLevel(Context& context, PlayerInfo& playerInfo, unsigned int numLevel);
        virtual LevelID::ID nextLevel() const;
    private:
        void buildScene();
};