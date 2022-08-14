/** @file Interactable.cpp */
#include "Objects/Nodes/Interactable.h"
#include "Objects/Nodes/PlayerNode.h"

Interactable::Interactable()
: Entity()
, mDistance(50)
, mIsInteractable(false)
{
    mCommand.category = Category::Player;
    mCommand.action = derivedAction<PlayerNode>([&] (PlayerNode& player, sf::Time) {
        if (Utility::distance(player, *this) <= mDistance)
            mIsInteractable = true;
        else
            mIsInteractable = false;
    });
}

bool Interactable::IsInteract() const
{
    return mIsInteractable;
}

void Interactable::setDistance(float distance)
{
    mDistance = distance;
}

unsigned int Interactable::getCategory() const 
{
    return Category::Interactable;
}

void Interactable::updateCurrent(sf::Time, CommandQueue& commands)
{
    commands.push(mCommand);
}