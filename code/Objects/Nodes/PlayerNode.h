/** @file PlayerNode.h */
#pragma once

#include "Objects/Nodes/Entity.h"
#include "App/Context.h"

class PlayerNode : public Entity
{
    public:
        PlayerNode(Context& context);
        void fire();
        void interact();
        void special();

        virtual unsigned int getCategory() const;
        virtual sf::FloatRect getBoundingRect() const;
        virtual void remove();
        virtual bool isMarkedForRemoval() const;
    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const; 
        virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
    private:
        Context& mContext;
        Command mFireCommand;
        bool mIsFire;
        Command mInteractCommand;
        bool mIsInteract;
        Command mSpecialCommand;
        bool mIsSpecial;
        sf::Sprite mSprite;            
};