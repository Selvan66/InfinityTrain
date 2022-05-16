/** @file Pickup.h */
#pragma once

#include "Objects/Nodes/Interactable.h"

class Pickup : public Interactable
{
    public:
        Pickup(Context& context, TexturesID texture);
        void setCommand(Command command);

        virtual sf::FloatRect getBoundingRect() const override;
        virtual void interact() override;
        virtual bool isDestroyed() const override;
    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override; 
        virtual void updateCurrent(sf::Time dt, CommandQueue& commands) override;
    private:
        sf::Sprite mSprite;
        bool mPickedUp;
        bool mIsDestroyed;
        Command mCommand;
};