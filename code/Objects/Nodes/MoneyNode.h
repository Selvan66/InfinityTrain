/** @file MoneyNode.h */
#pragma once

#include "Objects/Nodes/Interactable.h"

class MoneyNode : public Interactable
{
    public:
        MoneyNode(Context& context, unsigned int value);

        virtual sf::FloatRect getBoundingRect() const override;
        virtual void interact() override;
        virtual bool isDestroyed() const override;
    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override; 
        virtual void updateCurrent(sf::Time dt, CommandQueue& commands) override;
    private:
        unsigned int mValue;
        sf::Sprite mSprite;
        bool mPickedUp;
        bool mIsDestroyed;
        Command mCommand;
};