/** @file Level.h */
#pragma once

#include "Objects/Levels/LevelID.h"
#include "Objects/Levels/LvlContext.h"
#include "Objects/Nodes/PlayerNode.h"

class Level : public sf::NonCopyable {
public:
  typedef std::unique_ptr<Level> Ptr;

protected:
  enum Layer {
    Background,
    Floor,
    Battlefield,
    LayerCount
  };

public:
  explicit Level(
    LvlContext& lvlContext);
  CommandQueue& getCommandQueue();
  void draw();
  bool isPlayerAlive() const;

  virtual void update(sf::Time dt);
  virtual LevelID::ID nextLevel() const;

  static const sf::FloatRect
  getLevelBounds();

protected:
  bool isFinished() const;
  SceneNode*
  getLayer(Layer layer) const;
  LvlContext& getLvlContext() const;
  void setPlayerPos(sf::Vector2f pos);

private:
  void buildScene();
  void
  adaptNodesPosition(SceneNode* node);
  void updatePlayer(PlayerNode* player);
  void destoryEntitiesOutsideLevel();

private:
  LvlContext& mLvlContext;
  CommandQueue mCommands;
  SceneNode mSceneGraph;
  std::array<SceneNode*, LayerCount>
    mSceneLayer;
  PlayerNode* mPlayerNode;
};