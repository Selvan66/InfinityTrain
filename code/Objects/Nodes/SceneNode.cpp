/** @file SceneNode.cpp */
#include "Objects/Nodes/SceneNode.h"

bool collision(const SceneNode& lhs, const SceneNode& rhs)
{
    return lhs.getBoundingRect().intersects(rhs.getBoundingRect());
}

SceneNode::SceneNode(Category::Type category)
: mChildren()
, mParent(nullptr)
, mDefaultCategory(category)
{ }

void SceneNode::attachChild(Ptr child)
{
    child->mParent = this;
    mChildren.push_back(std::move(child));  
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
    auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](Ptr& p){ return p.get() == &node; });
    assert(found != mChildren.end());

    Ptr result = std::move(*found);
    result->mParent = nullptr;
    mChildren.erase(found);
    return result;    
}

void SceneNode::update(sf::Time dt, CommandQueue& commands)
{
    updateCurrent(dt, commands);
    updateChildren(dt, commands);
}

sf::Transform SceneNode::getWorldTransform() const
{
    sf::Transform transform = sf::Transform::Identity;

    for (const SceneNode* node = this; node != nullptr; node = node->mParent)
    {
        transform = node->getTransform() * transform;
    }

    return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
    return getWorldTransform() * sf::Vector2f();
}

void SceneNode::onCommand(const Command& command, sf::Time dt)
{
    if (command.category & getCategory())
    {
        command.action(*this, dt);
    }
    for (auto& child : mChildren)
    {
        child->onCommand(command, dt);
    }
}

void SceneNode::checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPair)
{
    if (this != &node && collision(*this, node) && !isDestroyed() && !node.isDestroyed())
    {
        collisionPair.insert(std::minmax(this, &node));
    }

    for (auto& child : mChildren)
    {
        child->checkNodeCollision(node, collisionPair);
    }
}

void SceneNode::checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPair)
{
    checkNodeCollision(sceneGraph, collisionPair);

    for (auto& child : sceneGraph.mChildren)
    {
        checkSceneCollision(*child, collisionPair);
    }
}

void SceneNode::removeObjects()
{
    auto wreckfieldBegin = std::remove_if(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::isMarkedForRemoval));
    mChildren.erase(wreckfieldBegin, mChildren.end());
    std::for_each(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::removeObjects));
}

unsigned int SceneNode::getCategory() const
{
    return mDefaultCategory;
}

sf::FloatRect SceneNode::getBoundingRect() const
{
    return sf::FloatRect();
}

bool SceneNode::isMarkedForRemoval() const
{
    return isDestroyed();
}

bool SceneNode::isDestroyed() const
{
    return false;
}

void SceneNode::updateChildren(sf::Time dt, CommandQueue& commands)
{
    for (auto& child : mChildren)
    {
        child->update(dt, commands);
    }
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto& child : mChildren)
    {
        child->draw(target, states);
    }
}

void SceneNode::drawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::FloatRect rect = getBoundingRect();
    sf::RectangleShape shape;
    shape.setPosition(sf::Vector2f(rect.left, rect.top));
    shape.setSize(sf::Vector2f(rect.width, rect.height));
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Green);
    shape.setOutlineThickness(1.f);

    target.draw(shape);
}

void SceneNode::updateCurrent(sf::Time dt, CommandQueue& commands)
{ }

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= sf::Transformable::getTransform();
    drawCurrent(target, states);
    drawChildren(target, states);
    drawBoundingRect(target, states);   //< Only for debug
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto& child : mChildren)
    {
        child->draw(target, states);
    }
}
