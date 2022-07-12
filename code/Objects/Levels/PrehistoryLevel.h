/** @file PrehistoryLevel.h */
#pragma once

#include "Objects/Levels/Level.h"

class PrehistoryLevel : public Level
{
    public:
        PrehistoryLevel(Context& context, PlayerInfo& playerInfo, unsigned int numLevel);

        virtual LevelID::ID nextLevel() const;
    private:
        void buildScene();       
};