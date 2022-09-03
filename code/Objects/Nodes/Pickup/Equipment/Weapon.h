/** @file Weapon.h */
#pragma once

#include "Objects/Nodes/Pickup/Pickup.h"

class Weapon : public Pickup
{
    public:
        Weapon(Context& context, int ammos, const sf::Time duration);

        void use();

        virtual bool action(PlayerNode& player) override;
        virtual std::string getDescription() const override;
    protected:
        void setCommand(Command command);

        virtual void updateCurrent(sf::Time dt, CommandQueue& commands) override;
    private:
        Command mAttackCommand;
        bool mUse;
        const sf::Time mDuration;
        sf::Time mElapsed;
};