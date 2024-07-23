/** @file Animation.cpp */
#include "Effects/Animation.h"
#include "Utils/Utility.h"

Animation::Animation()
  : mSprite(), mRect(), mLocalPixelBounds(), mFrameSize(), mNumFrames(),
    mCurrentFrame(0), mDuration(sf::Time::Zero), mElapsedTime(sf::Time::Zero),
    mRepeat(false), mReverse(false), mPaused(false) {}

Animation::Animation(const sf::Texture& texture)
  : mSprite(texture), mRect(0, 0, static_cast<int>(texture.getSize().x),
                            static_cast<int>(texture.getSize().y)),
    mLocalPixelBounds(), mFrameSize(), mNumFrames(), mCurrentFrame(0),
    mDuration(sf::Time::Zero), mElapsedTime(sf::Time::Zero), mRepeat(false),
    mReverse(false), mPaused(false) {}

Animation::Animation(const sf::Texture& texture, const sf::IntRect& rect)
  : mSprite(texture, rect), mRect(rect), mLocalPixelBounds(), mFrameSize(),
    mNumFrames(), mCurrentFrame(0), mDuration(sf::Time::Zero),
    mElapsedTime(sf::Time::Zero), mRepeat(false), mReverse(false),
    mPaused(false) {}

void Animation::setTexture(const sf::Texture& texture) {
  mSprite.setTexture(texture);
  mRect = sf::IntRect(0, 0, static_cast<int>(texture.getSize().x),
                      static_cast<int>(texture.getSize().y));
  mLocalPixelBounds = Utility::pixelLocalBounds(mSprite);
}

void Animation::setTexture(const sf::Texture& texture,
                           const sf::IntRect& rect) {
  mSprite.setTexture(texture);
  mSprite.setTextureRect(rect);
  mLocalPixelBounds = Utility::pixelLocalBounds(mSprite);
  mRect = rect;
}

void Animation::setFrameSize(sf::Vector2i frameSize) {
  mFrameSize = frameSize;
  mSprite.setTextureRect(
    sf::IntRect(mRect.left, mRect.top, mFrameSize.x, mFrameSize.y));
  mLocalPixelBounds = Utility::pixelLocalBounds(mSprite);
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
    mSprite.getTransform().transformRect(mLocalPixelBounds));
}

void Animation::update(sf::Time dt) {
  if (mPaused)
    return;

  sf::Time timePerFrame = mDuration / static_cast<float>(mNumFrames);
  mElapsedTime += dt;

  bool isTextureChanged = false;
  sf::IntRect textureRect = mSprite.getTextureRect();

  if (mCurrentFrame == 0) {
    isTextureChanged = true;
    textureRect = firstFrame();
    incrementCurrentFrame();
  }

  while ((mElapsedTime >= timePerFrame) &&
         ((mCurrentFrame < mNumFrames) || mRepeat)) {
    isTextureChanged = true;
    mElapsedTime -= timePerFrame;
    textureRect = nextFrame(textureRect);
    incrementCurrentFrame();
  }
  if (isTextureChanged) {
    mSprite.setTextureRect(textureRect);
    mLocalPixelBounds = Utility::pixelLocalBounds(mSprite);
  }
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
    if (rect.left < mRect.left) {
      rect.left = bounds.x - mFrameSize.x;
      rect.top -= mFrameSize.y;
      if (rect.top < 0)
        rect.top = bounds.y - mFrameSize.y;
    }
  } else {
    rect.left += mFrameSize.x;
    if (rect.left >= bounds.x) {
      rect.left = mRect.left;
      rect.top += mFrameSize.y;
      if (rect.top >= bounds.y)
        rect.top = mRect.top;
    }
  }

  return rect;
}

void Animation::incrementCurrentFrame() {
  mCurrentFrame++;
  if (mRepeat)
    mCurrentFrame %= (mNumFrames + 1);
}
