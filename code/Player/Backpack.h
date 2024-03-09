/** @file Backpack.h */
#pragma once

#include <array>
#include <queue>

#include "Player/Pocket.h"

class Backpack : public sf::Drawable,
                 public sf::Transformable,
                 public sf::NonCopyable {
public:
  explicit Backpack(Context &context);

  void addItemToBackpack(std::unique_ptr<Pickup> item);
  void giveItemToDrop(size_t index);
  void giveItemToUse(size_t index);
  void drop(sf::Vector2f pos, SceneNode &node);
  void action(PlayerNode &player);

  void handleEvent(const sf::Event &event);
  void update();
  void setPosition(sf::Vector2f position);

protected:
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;

private:
  size_t getFirstFreeIndex() const;

private:
  static constexpr size_t mSize = 20;
  std::array<Pocket, mSize> mBackpack;
  std::queue<std::unique_ptr<Pickup>> mDropQueue;
  std::queue<std::unique_ptr<Pickup>> mUseQueue;
};