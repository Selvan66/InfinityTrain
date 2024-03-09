/** @file PrehistoryLevel.h */
#pragma once

#include "Objects/Levels/Level.h"
#include "Objects/Nodes/Door.h"

class PrehistoryLevel : public Level {
public:
  explicit PrehistoryLevel(
    LvlContext& lvlContext);

  virtual void
  update(sf::Time dt) override;
  virtual LevelID::ID nextLevel() const;

private:
  void buildBackground();
  void buildFloor();
  void buildBattlefield();
  void buildScene();

private:
  Door* mDoor;
};