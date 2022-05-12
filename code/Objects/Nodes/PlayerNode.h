/** @file PlayerNode.h */
#pragma once

#include "Objects/Nodes/Entity.h"
#include "Objects/PlayerInfo.h"
#include "App/Context.h"

class PlayerNode : public Entity
{
    public:
        PlayerNode(Context& context, PlayerInfo& playerInfo);
        void fire();
        void interact();
        void special();
        void increaseMoney(unsigned int value);
        void increaseLive(int value);

        virtual unsigned int getCategory() const;
        virtual sf::FloatRect getBoundingRect() const;
    private:
        void adaptVelocity();

        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const; 
        virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
    private:
        Context& mContext;
        PlayerInfo& mPlayerInfo;
        Command mFireCommand;
        bool mIsFire;
        Command mInteractCommand;
        bool mIsInteract;
        Command mSpecialCommand;
        bool mIsSpecial;
        sf::Sprite mSprite;            
};