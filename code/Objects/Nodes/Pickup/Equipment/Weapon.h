/** @file Weapon.h */
#pragma once

#include "Objects/Nodes/Pickup/Pickup.h"
#include "Objects/Nodes/Pickup/Equipment/Projectile.h"
#include "Effects/Animation.h"

class Weapon : public Pickup
{
    public:
        enum Type
        {
            Knife,
            Sword,
            Bow,
            Bazooka,
            WeaponCount
        };
    public:
        Weapon(Context& context, Type type);
        Weapon(Context& context, Type type, int ammos);

        void use();
        sf::Vector2f getSize() const;

        virtual unsigned int getCategory() const override;
        virtual bool action(PlayerNode& player) override;
        virtual std::string getDescription() const override;
        virtual std::unordered_map<Stats::Type, int> getStats() const override;
    protected:    
        virtual std::unique_ptr<Pickup> create() const override;
        virtual sf::FloatRect getBoundingRect() const override;
        virtual void updateCurrent(sf::Time dt, CommandQueue& commands) override;
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    private:
        Command mAttackCommand;
        bool mUse;
        bool mAttacking;
        const Type mType;
        sf::Time mElapsed;
        Animation mAnimation;
};

struct WeaponParam
{
    const char* name;
    const int ammos;
    const int damage;
    const sf::Time duration;
    const TexturesID animation;
    const sf::IntRect animationRect;
    const size_t frameNum;
    const Projectile::Type projectile;
    const sf::Vector2f size;
};