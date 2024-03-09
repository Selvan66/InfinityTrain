/** @file Animation.cpp */
#include "Effects/Animation.h"
#include "Utils/Utility.h"

Animation::Animation()
  : mSprite(), mRect(), mFrameSize(), mNumFrames(), mCurrentFrame(0),
    mDuration(sf::Time::Zero), mElapsedTime(sf::Time::Zero), mRepeat(false),
    mReverse(false), mPaused(false) {}

Animation::Animation(const sf::Texture& texture)
  : mSprite(texture), mRect(0, 0, texture.getSize().x, texture.getSize().y),
    mFrameSize(), mNumFrames(), mCurrentFrame(0), mDuration(sf::Time::Zero),
    mElapsedTime(sf::Time::Zero), mRepeat(false), mReverse(false),
    mPaused(false) {}

Animation::Animation(const sf::Texture& texture, const sf::IntRect& rect)
  : mSprite(texture, rect), mRect(rect), mFrameSize(), mNumFrames(),
    mCurrentFrame(0), mDuration(sf::Time::Zero), mElapsedTime(sf::Time::Zero),
    mRepeat(false), mReverse(false), mPaused(false) {}

void Animation::setTexture(const sf::Texture& texture) {
  mSprite.setTexture(texture);
  mRect = sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y);
}

void Animation::setTexture(const sf::Texture& texture,
                           const sf::IntRect& rect) {
  mSprite.setTexture(texture);
  mRect = rect;
}

void Animation::setFrameSize(sf::Vector2i frameSize) {
  mFrameSize = frameSize;
  mSprite.setTextureRect(
    sf::IntRect(mRect.left, mRect.top, mFrameSize.x, mFrameSize.y));
  Utility::centerOrigin(mSprite);
}

void Animation::setNumFrames(std::size_t numFrames) { mNumFrames = numFrames; }

void Animation::setDuration(sf::Time duration) { mDuration = duration; }

void Animation::setRepeating(bool flag) { mRepeat = flag; }

void Animation::setReversed(bool flag) { mReverse = flag; }

void Animation::setColor(const sf::Color& color) { mSprite.setColor(color); }

void Animation::restart() {
  mCurrentFrame = 0;
  mElapsedTime = sf::Time::Zero;
}

void Animation::play() { mPaused = false; }

void Animation::pause() { mPaused = true; }

bool Animation::isFinished() const { return mCurrentFrame >= mNumFrames; }

sf::FloatRect Animation::getGlobalBounds() const {
  return sf::Transformable::getTransform().transformRect(
    mSprite.getGlobalBounds());
}

void Animation::update(sf::Time dt) {
  if (mPaused)
    return;

  sf::Time timePerFrame = mDuration / static_cast<float>(mNumFrames);
  mElapsedTime += dt;

  sf::IntRect textureRect = mSprite.getTextureRect();

  if (mCurrentFrame == 0) {
    textureRect = firstFrame();
    incrementCurrentFrame();
  }

  while ((mElapsedTime >= timePerFrame) &&
         ((mCurrentFrame < mNumFrames) || mRepeat)) {
    mElapsedTime -= timePerFrame;
    textureRect = nextFrame(textureRect);
    incrementCurrentFrame();
  }
  mSprite.setTextureRect(textureRect);
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= sf::Transformable::getTransform();
  target.draw(mSprite, states);
}

sf::IntRect Animation::firstFrame() const {
  if (mReverse)
    return sf::IntRect(mRect.left + mRect.width - mFrameSize.x,
                       mRect.top + mRect.height - mFrameSize.y, mFrameSize.x,
                       mFrameSize.y);

  return sf::IntRect(mRect.left, mRect.top, mFrameSize.x, mFrameSize.y);
}

sf::IntRect Animation::nextFrame(sf::IntRect rect) const {
  if (mRepeat && mCurrentFrame == 0)
    return firstFrame();

  sf::Vector2i bounds = {mRect.left + mRect.width, mRect.top + mRect.height};
  if (mReverse) {
    rect.left -= mFrameSize.x;
    if (rect.left - mFrameSize.x < mRect.left) {
      rect.left = bounds.x - mFrameSize.x;
      rect.top -= mFrameSize.y;
    }
  } else {
    rect.left += mFrameSize.x;
    if (rect.left + mFrameSize.x > bounds.x) {
      rect.left = mRect.left;
      rect.top += mFrameSize.y;
    }
  }

  return rect;
}

void Animation::incrementCurrentFrame() {
  mCurrentFrame++;
  if (mRepeat)
    mCurrentFrame %= (mNumFrames + 1);
}
