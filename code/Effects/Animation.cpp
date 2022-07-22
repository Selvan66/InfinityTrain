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
, mReverse(false)
{ }

Animation::Animation(const sf::Texture& texture)
: mSprite(texture)
, mFrameSize()
, mNumFrames()
, mCurrentFrame(0)
, mDuration(sf::Time::Zero)
, mElapsedTime(sf::Time::Zero)
, mRepeat(false)
, mReverse(false)
{ }

void Animation::setTexture(const sf::Texture& texture)
{
    mSprite.setTexture(texture);
}

void Animation::setFrameSize(sf::Vector2i frameSize)
{
    mFrameSize = frameSize;
    mSprite.setTextureRect(sf::IntRect(0, 0, mFrameSize.x, mFrameSize.y));
    Utility::centerOrigin(mSprite);
}

void Animation::setNumFrames(std::size_t numFrames)
{
    mNumFrames = numFrames;
}

void Animation::setDuration(sf::Time duration)
{
    mDuration = duration;
}

void Animation::setRepeating(bool flag)
{
    mRepeat = flag;
}

void Animation::setReversed(bool flag)
{
    mReverse = flag;
}

void Animation::restart()
{
    mCurrentFrame = 0;
    mElapsedTime = sf::Time::Zero;
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

    sf::IntRect textureRect = mSprite.getTextureRect();

    if (mCurrentFrame == 0)
    {
        textureRect = firstFrame();
        incrementCurrentFrame();
    }

    while ((mElapsedTime >= timePerFrame) && ((mCurrentFrame < mNumFrames) || mRepeat))
    {
        mElapsedTime -= timePerFrame;
        textureRect = nextFrame(textureRect);
        incrementCurrentFrame();
    }
    mSprite.setTextureRect(textureRect);
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= sf::Transformable::getTransform();
    target.draw(mSprite, states);
}

sf::IntRect Animation::firstFrame() const
{
    if (mReverse)
    {
        sf::Vector2i bounds(mSprite.getTexture()->getSize());
        return sf::IntRect(bounds.x - mFrameSize.x, bounds.y - mFrameSize.y, mFrameSize.x, mFrameSize.y);
    }

    return sf::IntRect(0, 0, mFrameSize.x, mFrameSize.y);
}

sf::IntRect Animation::nextFrame(sf::IntRect rect) const
{
    if (mRepeat && mCurrentFrame == 0)
        return firstFrame();

    sf::Vector2i bounds(mSprite.getTexture()->getSize());
    if (mReverse)
    {
        rect.left -= mFrameSize.x;
        if (rect.left - mFrameSize.x < 0)
        {
            rect.left = bounds.x - mFrameSize.x;
            rect.top -= mFrameSize.y;
        }
    }
    else
    {
        rect.left += mFrameSize.x;
        if (rect.left + mFrameSize.x > bounds.x)
        {
            rect.left = 0;
            rect.top += mFrameSize.y;
        }
    }

    return rect;
}

void Animation::incrementCurrentFrame()
{
    mCurrentFrame++;
    if (mRepeat)
        mCurrentFrame %= (mNumFrames + 1);  
}