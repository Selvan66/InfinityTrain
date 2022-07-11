/** @file Animation.cpp */
#include "Effects/Animation.h"
#include "Utils/Utility.h"

Animation::Animation()
: mSprite()
, mFrameSize()
, mNumFrames()
, mCurrentFrame(0)
, mDuration(sf::Time::Zero)
, mElapsedTime(sf::Time::Zero)
, mRepeat(false)
{ }

Animation::Animation(const sf::Texture& texture)
: mSprite(texture)
, mFrameSize()
, mNumFrames()
, mCurrentFrame(0)
, mDuration(sf::Time::Zero)
, mElapsedTime(sf::Time::Zero)
, mRepeat(false)
{ }

void Animation::setTexture(const sf::Texture& texture)
{
    mSprite.setTexture(texture);
}

const sf::Texture& Animation::getTexture() const
{
    return *mSprite.getTexture();
}

void Animation::setFrameSize(sf::Vector2i frameSize)
{
    mFrameSize = frameSize;
    mSprite.setTextureRect(sf::IntRect(0, 0, mFrameSize.x, mFrameSize.y));
    Utility::centerOrigin(mSprite);
}

sf::Vector2i Animation::getFrameSize() const
{
    return mFrameSize;
}

void Animation::setNumFrames(std::size_t numFrames)
{
    mNumFrames = numFrames;
}

std::size_t Animation::getNumFrames() const
{
    return mNumFrames;
}

void Animation::setDuration(sf::Time duration)
{
    mDuration = duration;
}

sf::Time Animation::getDuration() const
{
    return mDuration;
}

void Animation::setRepeating(bool flag)
{
    mRepeat = flag;
}

bool Animation::isRepeating() const
{
    return mRepeat;
}

void Animation::restart()
{
    mCurrentFrame = 0;
}

bool Animation::isFinished() const
{
    return mCurrentFrame >= mNumFrames;
}

sf::FloatRect Animation::getGlobalBounds() const
{
    return sf::Transformable::getTransform().transformRect(mSprite.getGlobalBounds());
}

void Animation::update(sf::Time dt)
{
    sf::Time timePerFrame = mDuration / static_cast<float>(mNumFrames);
    mElapsedTime += dt;

    sf::Vector2i textureBounds(mSprite.getTexture()->getSize());
    sf::IntRect textureRect = mSprite.getTextureRect();

    if (mCurrentFrame == 0)
        textureRect = sf::IntRect(0, 0, mFrameSize.x, mFrameSize.y);

    while (mElapsedTime >= timePerFrame && (mCurrentFrame < mNumFrames || mRepeat)) 
    {
        textureRect.left += textureRect.width;

        if (textureRect.left + textureRect.width > textureBounds.x) {
            textureRect.left = 0;
            textureRect.top += textureRect.height;
        }

        mElapsedTime -= timePerFrame;

        if (mRepeat) 
        {
            mCurrentFrame = (mCurrentFrame + 1) % mNumFrames;
            if (mCurrentFrame == 0)
                textureRect = sf::IntRect(0, 0, mFrameSize.x, mFrameSize.y);
        }
        else 
        {
            mCurrentFrame++;
        }
    }
    mSprite.setTextureRect(textureRect);
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= sf::Transformable::getTransform();
    target.draw(mSprite, states);
}
