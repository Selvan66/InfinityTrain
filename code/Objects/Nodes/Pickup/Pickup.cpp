/** @file Pickup.cpp */
#include "spdlog/spdlog.h"

#include "Objects/Nodes/Pickup/Pickup.h"
#include "Objects/Nodes/PlayerNode.h"
#include "Objects/Nodes/TextNode.h"
#include "Utils/Utility.h"

Pickup::Pickup(Context& context)
  : Interactable(), mContext(context), mSprite(), mPickedUp(false), mCommand() {
  mCommand.category = Category::Player;
  mCommand.action =
    derivedAction<PlayerNode>([this](PlayerNode& player, sf::Time) {
      spdlog::debug("Pickup::Pickup | Picked {}", this->getName());
      player.pickup(create());
      this->destroy();
    });
}

std::string Pickup::getName() const { return ""; }
std::string Pickup::getDescription() const { return getName(); }

std::unordered_map<Stats::Type, int> Pickup::getStats() const { return {{}}; }

bool Pickup::action(PlayerNode& player) {
  spdlog::debug("Pickup::action");
  player.pickup(create());
  return true;
}

void Pickup::interact() { mPickedUp = true; }

sf::FloatRect Pickup::getBoundingRect() const {
  return SceneNode::getWorldTransform().transformRect(
    mSprite.getGlobalBounds());
}

void Pickup::drawCurrent(sf::RenderTarget& target,
                         sf::RenderStates states) const {
  target.draw(mSprite, states);
}

std::unique_ptr<Pickup> Pickup::create() const {
  return std::unique_ptr<Pickup>(new Pickup(mContext));
}

void Pickup::setTexture(TexturesID texture) {
  mSprite.setTexture(mContext.textures.get(texture));
  Utility::centerOrigin(mSprite);
}

void Pickup::setCommand(Command command) { mCommand = command; }

Context& Pickup::getContext() const { return mContext; }

void Pickup::setLabel(const std::string& text) {
  std::unique_ptr<TextNode> textNode(new TextNode(mContext));
  textNode->setPosition(0.f, -40.f);
  textNode->setString(text);
  SceneNode::attachChild(std::move(textNode));
}

void Pickup::updateCurrent(sf::Time dt, CommandQueue& commands) {
  Interactable::updateCurrent(dt, commands);

  if (mPickedUp) {
    spdlog::trace("Pickup::updateCurrent | Add pickup command");
    commands.push(mCommand);
    mPickedUp = false;
  }
}
