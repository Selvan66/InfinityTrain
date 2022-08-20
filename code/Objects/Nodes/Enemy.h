/** @file Enemy.h */
#pragma once

#include "Objects/Nodes/Entity.h"
#include "Objects/Nodes/PlayerNode.h"

class Enemy : public Entity
{
    public:
        Enemy(Context& context);
    protected:
        virtual void updateCurrent(sf::Time dt, CommandQueue& commands) override;
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    private:
        sf::Sprite mSprite;
        PlayerNode* mPlayer;
};