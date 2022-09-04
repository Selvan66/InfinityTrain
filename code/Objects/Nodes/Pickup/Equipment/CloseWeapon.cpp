/** @file CloseWeapon.cpp */
#pragma once

#include "Objects/Nodes/Pickup/Equipment/CloseWeapon.h"
#include "Objects/Nodes/Enemy.h"

static std::array<CloseWeaponParam, CloseWeapon::CloseWeaponCount> closeWeapons = 
{
    {
        { "Knife", 25, 25, sf::seconds(1), TexturesID::Knife, sf::IntRect(0, 0, 32, 32) }
    }
};

CloseWeapon::CloseWeapon(Context& context, size_t index)
: CloseWeapon(context, index, closeWeapons[index].ammos)
{ }

CloseWeapon::CloseWeapon(Context& context, size_t index, int ammos)
: Weapon(context, ammos, closeWeapons[index].duration)
, mIndex(index)
, mAnimation(context.textures.get(closeWeapons[index].animation))
{
    mAnimation.setFrameSize({closeWeapons[index].animationRect.width, closeWeapons[index].animationRect.height});
    mAnimation.setNumFrames(1);
    mAnimation.setDuration(closeWeapons[index].duration);

    Command command;
    command.category = Category::Enemy;
    command.action = derivedAction<Enemy>([&](Enemy& enemy, sf::Time dt)    // You cant attack if there's no enemy
    {
        if (Utility::collision(*this, enemy))
            enemy.damage(closeWeapons[mIndex].damage);
    });
    Weapon::setCommand(command);

    Pickup::setTexture(closeWeapons[index].animation);
    Pickup::setName(closeWeapons[index].name);
}

std::unordered_map<Stats::Type, int> CloseWeapon::getStats() const 
{
    return { { Stats::Attack, closeWeapons[mIndex].damage } };
}

sf::FloatRect CloseWeapon::getBoundingRect() const 
{
    return SceneNode::getWorldTransform().transformRect(mAnimation.getGlobalBounds());
}

std::unique_ptr<Pickup> CloseWeapon::create() const 
{
    return std::unique_ptr<Pickup>(new CloseWeapon(Pickup::getContext(), mIndex, Entity::getHitpoints()));   
}

void CloseWeapon::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    Weapon::updateCurrent(dt, commands);
    mAnimation.update(dt);
}
