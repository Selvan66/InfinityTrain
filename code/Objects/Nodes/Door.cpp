/** @file Door.cpp */
#include "Objects/Nodes/Door.h"


Door::Door(Context& context, bool toClose)
: Interactable()
, mIsOpen(false)
, mInteract(false)
, mBackground({152, 82})
, mAnimation()
{
    Interactable::setDistance(100.f);
    Utility::centerOrigin(mBackground);

    if (toClose)
    {
        mAnimation.setTexture(context.textures.get(TexturesID::OpenDoors));
        mAnimation.setNumFrames(2);
        mIsOpen = true;
        sf::Transformable::setRotation(180);
    }
    else
    {
        mAnimation.setTexture(context.textures.get(TexturesID::CloseDoors));
        mAnimation.setNumFrames(3); 
    }
    mAnimation.setDuration(sf::seconds(2));
    mAnimation.setRepeating(false);
    mAnimation.setFrameSize({150, 82});
    mAnimation.update(sf::seconds(0));
}

void Door::interact()
{
    if (mIsOpen)
        mInteract = true;
}

sf::FloatRect Door::getBoundingRect() const 
{
    return sf::Transformable::getTransform().transformRect(mAnimation.getGlobalBounds());
}

void Door::open()
{
    mIsOpen = true;
}

void Door::close()
{
    mIsOpen = false;
}

bool Door::isInteract() const
{
    return mInteract;
}

void Door::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    Interactable::updateCurrent(dt, commands);
    if (mIsOpen)
        mAnimation.update(dt);
}

void Door::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const 
{
    target.draw(mBackground, states);
    target.draw(mAnimation, states);
}


