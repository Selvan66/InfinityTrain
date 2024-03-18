/** @file Door.cpp */
#include "Objects/Nodes/Door.h"
#include "App/Context.h"
#include "Utils/Utility.h"

Door::Door(Context& context)
  : Interactable(), mIsOpen(false), mInteract(false), mBackground({152, 82}),
    mAnimation(context.textures.get(TexturesID::Door)) {
  Interactable::setDistance(100.f);
  Utility::centerOrigin(mBackground);

  mAnimation.setDuration(sf::seconds(2));
  mAnimation.setNumFrames(4);
  mAnimation.setReversed(true);
  mAnimation.setFrameSize({150, 82});
}

void Door::open() {
  if (!mIsOpen) {
    mIsOpen = true;
    mAnimation.setReversed(false);
    mAnimation.restart();
  }
}

void Door::close() {
  if (mIsOpen) {
    mIsOpen = false;
    mAnimation.setReversed(true);
    mAnimation.restart();
  }
}

bool Door::isInteract() const { return mInteract; }

void Door::interact() {
  if (mIsOpen)
    mInteract = true;
}

sf::FloatRect Door::getBoundingRect() const {
  return SceneNode::getWorldTransform().transformRect(
    mAnimation.getGlobalBounds());
}

void Door::updateCurrent(sf::Time dt, CommandQueue& commands) {
  Interactable::updateCurrent(dt, commands);
  mAnimation.update(dt);
}

void Door::drawCurrent(sf::RenderTarget& target,
                       sf::RenderStates states) const {
  target.draw(mBackground, states);
  target.draw(mAnimation, states);
}
