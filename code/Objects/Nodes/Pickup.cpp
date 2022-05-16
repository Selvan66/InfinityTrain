/** @file Pickup.cpp */
#include "Objects/Nodes/Pickup.h"

Pickup::Pickup(Context& context, TexturesID texture)
: Interactable(context)
, mSprite(context.textures.get(texture))
, mPickedUp(false)
, mIsDestroyed(false)
, mCommand()
{
    Utility::centerOrigin(mSprite);
    Interactable::setTextPos({0, -mSprite.getLocalBounds().height});
}

void Pickup::setCommand(Command command)
{
    mCommand = command;
}

sf::FloatRect Pickup::getBoundingRect() const 
{
    return sf::Transformable::getTransform().transformRect(mSprite.getGlobalBounds());
}

void Pickup::interact()
{
    mPickedUp = true;
}

bool Pickup::isDestroyed() const 
{
    return mIsDestroyed;
}

void Pickup::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const 
{
    target.draw(mSprite, states);
}

void Pickup::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    Interactable::updateCurrent(dt, commands);

    if (mPickedUp && !mIsDestroyed)
    {
        commands.push(mCommand);
        mPickedUp = false;
        mIsDestroyed = true;
    }
}
