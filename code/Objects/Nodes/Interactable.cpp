/** @file Interactable.cpp */
#include "Objects/Nodes/Interactable.h"
#include "Objects/Nodes/PlayerNode.h"

Interactable::Interactable(Context& context)
: mDistance(0.f)
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

void Interactable::setDistance(float distance)
{
    mDistance = distance;
}

bool Interactable::IsInteract() const
{
    return mIsInteractable;
}

void Interactable::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    commands.push(mCommand);
}
