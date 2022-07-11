/** @file Door.h */
#pragma once

#include "Objects/Nodes/Interactable.h"
#include "Effects/Animation.h"

class Door : public Interactable
{
    public:
        Door(Context& context, bool toClose);
        void open();
        void close();
        bool isInteract() const;

        virtual void interact() override;
    protected:
        virtual sf::FloatRect getBoundingRect() const override;
        virtual void updateCurrent(sf::Time dt, CommandQueue& commands) override;
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    private:
        bool mIsOpen;
        bool mInteract;
        sf::RectangleShape mBackground;
        Animation mAnimation;
};