/** @file DistanceWeapon.h */
#pragma once

#include "Objects/Nodes/Pickup/Equipment/Weapon.h"

class DistanceWeapon : public Weapon
{
    public:
        enum Type
        {
            Gun,
            DistanceWeaponCount
        };
    public:
        DistanceWeapon(Context& context, size_t index);
        DistanceWeapon(Context& context, size_t index, int ammos);
    protected:
        virtual std::unique_ptr<Pickup> create() const override;
    private:
        size_t mIndex;
};

struct DistanceWeaponParam
{
    const char* name;
    const int ammos;
    // Projectile::Type mProjectileType;
    const TexturesID texture;
    const sf::IntRect textureRect;
};