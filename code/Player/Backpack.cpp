/** @file Backpack.cpp */
#include <limits>

#include "spdlog/spdlog.h"

#include "Objects/Nodes/PlayerNode.h"
#include "Player/Backpack.h"

#define V1_POCKET Pocket(context)
#define V4_POCKET V1_POCKET, V1_POCKET, V1_POCKET, V1_POCKET
#define V20_POCKET V4_POCKET, V4_POCKET, V4_POCKET, V4_POCKET, V4_POCKET

Backpack::Backpack(Context& context)
  : mBackpack{V20_POCKET}, mDropQueue(), mUseQueue() {
  for (size_t i = 0; i < mSize; ++i)
    mBackpack[i].setLeftClickCallback([this, i]() {
      spdlog::trace("Backpack::Backpack | Left click on backpack slot nr {}",
                    i);
      this->giveItemToUse(i);
    });

  for (size_t i = 0; i < mSize; ++i)
    mBackpack[i].setRightClickCallback([this, i]() {
      spdlog::trace("Backpack::Backpack | Right click on backpack slot nr {}",
                    i);
      this->giveItemToDrop(i);
    });

  for (size_t i = 0; i < 4; ++i)
    for (size_t j = 0; j < 5; ++j)
      mBackpack[i * 5 + j].setPosition(static_cast<float>(j * 40),
                                       static_cast<float>(i * 40));
}

void Backpack::addItemToBackpack(std::unique_ptr<Pickup> item) {
  size_t index = getFirstFreeIndex();

  if (index == std::numeric_limits<size_t>::max()) {
    giveItemToDrop(0);
    index = 0;
  }

  spdlog::trace("Backpack::addItemToBackpack | To slot {} add item {}", index,
                item->getDescription());

  mBackpack[index].addItem(std::move(item));
}

void Backpack::giveItemToDrop(size_t index) {
  if (!mBackpack[index].isItem()) {
    spdlog::warn("Backpack::giveItemToDrop | Cannot empty slot {} without item",
                 index);
    return;
  }
  spdlog::trace("Backpack::giveItemToDrop | Drop slot {}", index);
  mDropQueue.push(mBackpack[index].dropItem());
}

void Backpack::giveItemToUse(size_t index) {
  if (!mBackpack[index].isItem()) {
    spdlog::warn("Backpack::giveItemToUse | Cannot use empty slot {}", index);
    return;
  }
  spdlog::trace("Backpack::giveItemToUse | Use slot {}", index);
  mUseQueue.push(mBackpack[index].dropItem());
}

void Backpack::drop(sf::Vector2f pos, SceneNode& node) {
  while (!mDropQueue.empty()) {
    mDropQueue.front()->setPosition(pos);
    node.attachChild(std::move(mDropQueue.front()));
    mDropQueue.pop();
  }
}

void Backpack::action(PlayerNode& player) {
  while (!mUseQueue.empty()) {
    auto pickup = std::move(mUseQueue.front());
    if (!pickup->action(player)) {
      spdlog::trace("Backpack::action | Cannot use item {}",
                    pickup->getDescription());
      addItemToBackpack(std::move(pickup));
    }
    mUseQueue.pop();
  }
}

void Backpack::handleEvent(const sf::Event& event) {
  for (auto& pocket : mBackpack)
    pocket.handleEvent(event);
}

void Backpack::update() {
  for (auto& pocket : mBackpack)
    pocket.update();
}

void Backpack::setPosition(sf::Vector2f position) {
  for (auto& pocket : mBackpack)
    pocket.move(position);
}

void Backpack::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= sf::Transformable::getTransform();
  for (auto& pocket : mBackpack)
    target.draw(pocket, states);
}

size_t Backpack::getFirstFreeIndex() const {
  for (size_t i = 0; i < mSize; ++i)
    if (!mBackpack[i].isItem())
      return i;
  return std::numeric_limits<size_t>::max();
}
