/** @file Enemy.cpp */
#include "spdlog/spdlog.h"

#include "Objects/Nodes/Enemy/Enemy.h"
#include "Utils/Utility.h"

Enemy::Enemy(Context& context)
  : Entity(100), mContext(context),
    mAnimation(context.textures.get(TexturesID::Dog)), mPlayer(nullptr),
    mDuration(sf::Time::Zero), mText(nullptr),
    mDamageDuration(sf::seconds(0.3f)) {

  mAnimation.setFrameSize({64, 64});
  mAnimation.setNumFrames(4);
  mAnimation.setDuration(sf::seconds(0.5f));
  mAnimation.setRepeating(true);

  std::unique_ptr<TextNode> text(new TextNode(context));
  text->setString(std::to_string(Entity::getHitpoints()) + "HP");
  text->setPosition(0.f, -40.f);
  mText = text.get();
  SceneNode::attachChild(std::move(text));
}

sf::FloatRect Enemy::getBoundingRect() const {
  return SceneNode::getWorldTransform().transformRect(
    mAnimation.getGlobalBounds());
}

unsigned int Enemy::getCategory() const { return Category::Enemy; }

bool Enemy::damage(int points) {
  spdlog::trace("Enemy::damage | Hit - {}", points);
  mDamageDuration = sf::Time::Zero;
  return Entity::damage(points);
}

bool Enemy::isMarkedForRemoval() const {
  if (SceneNode::isMarkedForRemoval())
    mContext.statistics.increase(Statistics::KilledEnemies);
  return SceneNode::isMarkedForRemoval();
}

void Enemy::updateCurrent(sf::Time dt, CommandQueue& commands) {
  mDamageDuration += dt;
  if (mDamageDuration < sf::seconds(0.3f))
    mAnimation.setColor(sf::Color::Red);
  else
    mAnimation.setColor(sf::Color::White);

  Entity::updateCurrent(dt, commands);
  mAnimation.update(dt);

  if (mPlayer == nullptr) {
    Command command;
    command.category = Category::Player;
    command.action =
      derivedAction<PlayerNode>([&](PlayerNode& player, sf::Time) {
        spdlog::trace("Enemy::updateCurrent | Find player command");
        mPlayer = &player;
      });
    commands.push(command);
  } else {
    sf::Vector2f direction =
      mPlayer->getWorldPosition() - SceneNode::getWorldPosition();
    float length =
      std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0.f) {
      direction /= length;
      Entity::accelerate(direction * 25.f);
    }
  }

  Command command;
  command.category = Category::Player;
  command.action = derivedAction<PlayerNode>(
    [&duration = mDuration, this](PlayerNode& player, sf::Time dt) {
      duration += dt;
      if (duration >= sf::seconds(0.5f)) {
        if (Utility::collision(*this, player)) {
          spdlog::trace("Enemy::updateCurrent | Hit player command");
          player.damageWithKnockback(25, SceneNode::getWorldPosition());
          duration = sf::Time::Zero;
        }
      }
    });
  commands.push(command);

  mText->setString(std::to_string(Entity::getHitpoints()) + "HP");
}

void Enemy::drawCurrent(sf::RenderTarget& target,
                        sf::RenderStates states) const {
  target.draw(mAnimation, states);
}
