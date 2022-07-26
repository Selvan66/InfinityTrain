/** @file Pickup.h */
#pragma once

#include "Objects/Nodes/Interactable.h"

class Pickup : public Interactable
{
    public:
        Pickup(Context& context, TexturesID texture);
        void setCommand(Command command);

        virtual void use(PlayerNode& player) = 0;
        
        virtual void interact() override;
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override; 
    protected:
        void addText(const std::string& text);

        virtual sf::FloatRect getBoundingRect() const override;
        virtual void updateCurrent(sf::Time dt, CommandQueue& commands) override;
    private:
        Context& mContext;
        sf::Sprite mSprite;
        bool mPickedUp;
        Command mCommand;
};