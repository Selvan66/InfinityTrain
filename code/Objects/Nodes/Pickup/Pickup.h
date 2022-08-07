/** @file Pickup.h */
#pragma once

#include "Objects/Nodes/Interactable.h"

class PlayerNode;

class Pickup : public Interactable
{
    public:
        Pickup(Context& context);
        std::string getDescription() const;

        virtual bool use(PlayerNode& player);
        
        virtual void interact() override;
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override; 
    protected:
        void setTexture(TexturesID texture);
        void setCommand(Command command);
        void addText(const std::string& text);
        void addDescription(const std::string& description);

        virtual sf::FloatRect getBoundingRect() const override;
        virtual void updateCurrent(sf::Time dt, CommandQueue& commands) override;
    private:
        Context& mContext;
        sf::Sprite mSprite;
        bool mPickedUp;
        Command mCommand;
        std::string mDescription;
};