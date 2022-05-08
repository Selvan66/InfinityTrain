/** @file PrehistoryLevel.h */
#pragma once

#include "Objects/Levels/Level.h"

class PrehistoryLevel : public Level
{
    public:
        PrehistoryLevel(Context& context);
    private:
        void buildScene();
};