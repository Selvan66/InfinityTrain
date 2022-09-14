/** @file CloseWeapon.h */
#pragma once

#include "Objects/Nodes/Pickup/Equipment/Weapon.h"
#include "Effects/Animation.h"

class CloseWeapon : public Weapon
{
    public: 
        enum Type
        {
            Knife,
            Sword,
            CloseWeaponCount
        };
    public:
        CloseWeapon(Context& context, size_t index);
        CloseWeapon(Context& context, size_t index, int ammos);
    
        virtual std::unordered_map<Stats::Type, int> getStats() const override;
    protected:
        virtual sf::FloatRect getBoundingRect() const override;
        virtual std::unique_ptr<Pickup> create() const override;

        virtual void used() override;
        virtual void updateCurrent(sf::Time dt, CommandQueue& commands) override;
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    private:
        size_t mIndex;
        Animation mAnimation;
        sf::Time mDuration;
};

struct CloseWeaponParam
{
    const char* name;
    const int ammos;
    const int damage;
    sf::Time duration;
    const TexturesID animation;
    const sf::IntRect animationRect;
    const size_t frameNum;
};