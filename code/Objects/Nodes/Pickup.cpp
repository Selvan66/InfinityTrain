/** @file Pickup.cpp */
#include "Objects/Nodes/Pickup.h"

Pickup::Pickup(Context& context, TexturesID texture)
: Interactable()
, mSprite(context.textures.get(texture))
, mPickedUp(false)
, mCommand()
{
    Utility::centerOrigin(mSprite);
}

void Pickup::setCommand(Command command)
{
    mCommand = command;
}

void Pickup::interact()
{
    mPickedUp = true;
}

void Pickup::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const 
{
    target.draw(mSprite, states);
}

sf::FloatRect Pickup::getBoundingRect() const 
{
    return sf::Transformable::getTransform().transformRect(mSprite.getGlobalBounds());
}

void Pickup::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    Interactable::updateCurrent(dt, commands);

    if (mPickedUp)
        commands.push(mCommand);
}