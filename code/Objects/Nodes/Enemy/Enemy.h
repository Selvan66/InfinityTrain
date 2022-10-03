/** @file Enemy.h */
#pragma once

#include "Objects/Nodes/Entity.h"
#include "Objects/Nodes/PlayerNode.h"
#include "Objects/Nodes/TextNode.h"

class Enemy : public Entity
{
    public:
        Enemy(Context& context);

        virtual sf::FloatRect getBoundingRect() const override;
        virtual unsigned int getCategory() const override;
        virtual bool damage(int points) override;
        virtual bool isMarkedForRemoval() const override;
    protected:
        virtual void updateCurrent(sf::Time dt, CommandQueue& commands) override;
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    private:
        Context& mContext;
        sf::Sprite mSprite;
        PlayerNode* mPlayer;
        sf::Time mDuration;
        TextNode* mText;
        sf::Time mDamageDuration;
};