/** @file StartLevel.h */
#pragma once

#include "Objects/Levels/Level.h"
#include "Objects/Nodes/Door.h"

class StartLevel : public Level
{
    public:
        explicit StartLevel(LvlContext& lvlContext);

        virtual void update(sf::Time dt) override;
        virtual LevelID::ID nextLevel() const override;
    private:
        void buildBackground();
        void buildFloor();
        void buildBattlefield();
        void buildScene();
    private:
        Door* mDoor;
};