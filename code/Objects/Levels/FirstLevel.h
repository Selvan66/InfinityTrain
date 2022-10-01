/** @file FirstLevel.h */
#pragma once

#include "Objects/Levels/Level.h"
#include "Objects/Nodes/Door.h"

class FirstLevel : public Level
{
    public:
        explicit FirstLevel(LvlContext& lvlContext);
        
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