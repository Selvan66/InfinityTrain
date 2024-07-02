/** @file Map.h */
#pragma once
#include <functional>

#include "spdlog/spdlog.h"

#include "Objects/Levels/Level.h"

class Map {
public:
  explicit Map(Context& context);
  void update(sf::Time dt);
  void handleEvent(const sf::Event& event);
  void draw();
  bool isPlayerAlive() const;

private:
  template <typename T> void registerLevel(LevelID::ID id);
  void registerLevels();

private:
  Level::Ptr mLevel;
  LvlContext mLvlContext;
  std::array<std::function<Level::Ptr()>, LevelID::LevelCount> mFactories;
  unsigned long long mStartTime;
  ParserGui::GuiParsePtr mGui;
};

template <typename T> void Map::registerLevel(LevelID::ID id) {
  spdlog::info("Map::registerLevel | Register level {}", static_cast<int>(id));
  mFactories[id] = [this] { return std::make_unique<T>(mLvlContext); };
}
