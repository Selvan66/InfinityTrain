/** @file Weapon.cpp */
#include "Objects/Nodes/Pickup/Equipment/Weapon.h"
#include "Objects/Nodes/PlayerNode.h"

Weapon::Weapon(Context& context, int ammos)
: Pickup(context)
, mUse(false)
{
    Command command;
    command.category = Category::Player;
    command.action = derivedAction<PlayerNode>([&](PlayerNode& player, sf::Time) {
        player.pickup(create());
        this->destroy();
    });
    Pickup::setCommand(command);
    Entity::setHitpoints(ammos);
}

void Weapon::use()
{
    mUse = true;
}

bool Weapon::action(PlayerNode& player)
{
    player.pickup(create());
    return true;
}

std::string Weapon::getDescription() const 
{
    std::stringstream ss;
    ss << getName() << '\n';
    ss << "Ammos: " << Entity::getHitpoints();
    return ss.str();
}

void Weapon::setCommand(Command command)
{
    mAttackCommand = command;
}

void Weapon::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    if (mUse)
    {
        commands.push(mAttackCommand);
        mUse = false;
    }
}