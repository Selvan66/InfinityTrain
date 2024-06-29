/** @file SceneNode.h */
#pragma once

#include <memory>
#include <set>
#include <vector>

#include "SFML/Graphics.hpp"

#include "Objects/Category.h"
#include "Objects/CommandQueue.h"

class SceneNode : public sf::Transformable,
                  public sf::Drawable,
                  public sf::NonCopyable {
public:
  typedef std::unique_ptr<SceneNode> Ptr;
  typedef std::pair<SceneNode*, SceneNode*> Pair;

public:
  explicit SceneNode(Category::Type category = Category::None);
  virtual ~SceneNode() = default;

  void attachChild(Ptr child);
  Ptr detachChild(const SceneNode& node);
  size_t getChildrenSize() const;
  bool isChildAttach(const SceneNode& ptr);
  void update(sf::Time dt, CommandQueue& commands);
  sf::Transform getWorldTransform() const;
  sf::Vector2f getWorldPosition() const;
  void onCommand(const Command& command, sf::Time dt);
  void checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPair);
  void checkSceneCollision(SceneNode& sceneGraph,
                           std::set<Pair>& collisionPair);
  void removeObjects();

  virtual unsigned int getCategory() const;
  virtual sf::FloatRect getBoundingRect() const;
  virtual bool isMarkedForRemoval() const;
  virtual bool isDestroyed() const;

protected:
  virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
  virtual void drawCurrent(sf::RenderTarget& target,
                           sf::RenderStates states) const;

  virtual void draw(sf::RenderTarget& target,
                    sf::RenderStates states) const override;

private:
  void updateChildren(sf::Time dt, CommandQueue& commands);
  void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
  void drawBoundingRect(sf::RenderTarget& target,
                        sf::RenderStates states) const; //<Only for debug
private:
  std::vector<Ptr> mChildren;
  SceneNode* mParent;
  Category::Type mDefaultCategory;
};
