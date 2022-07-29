/** @file PlayerNode.h */
#pragma once

#include "Objects/Nodes/Entity.h"
#include "Player/PlayerInfo.h"
#include "App/Context.h"

class PlayerNode : public Entity
{
    public:
        enum Action
        {
            MoveUp,
            MoveDown,
            MoveLeft,
            MoveRight,
            Fire,
            Interact,
            Special
        };
    public:
        PlayerNode(Context& context, PlayerInfo& playerInfo);
        
        void makeAction(Action action);
        void pickup(std::unique_ptr<Pickup> pickup);
        bool updateStat(Stats::Type stat, int value);
    protected:
        virtual unsigned int getCategory() const override;
        virtual sf::FloatRect getBoundingRect() const override;
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override; 
        virtual void updateCurrent(sf::Time dt, CommandQueue& commands) override;
    private:
        void fire();
        void interact();
        void special();
        void adaptVelocity();
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