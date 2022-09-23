/** @file Enemy.cpp */
#pragma once

#include "Objects/Nodes/Enemy.h"


Enemy::Enemy(Context& context)
: Entity(100)
, mSprite(context.textures.get(TexturesID::Player), {0, 0, 80, 61})
, mPlayer(nullptr)
, mDuration(sf::Time::Zero)
, mText(nullptr)
{ 
    Utility::centerOrigin(mSprite);
    std::unique_ptr<TextNode> text(new TextNode(context));
    text->setString(std::to_string(Entity::getHitpoints()) + "HP");
    text->setPosition(0.f, -40.f);
    mText = text.get();
    SceneNode::attachChild(std::move(text));
}

sf::FloatRect Enemy::getBoundingRect() const 
{
    return SceneNode::getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

unsigned int Enemy::getCategory() const 
{
    return Category::Enemy;
}

void Enemy::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    Entity::updateCurrent(dt, commands);
    if (mPlayer == nullptr)
    {
        Command command;
        command.category = Category::Player;
        command.action = derivedAction<PlayerNode>([&](PlayerNode& player, sf::Time) {
            mPlayer = &player;
        });
        commands.push(command);
    }
    else
    {
        sf::Vector2f direction = mPlayer->getWorldPosition() - SceneNode::getWorldPosition();
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > 0.f)
        {
            direction /= length;
            Entity::accelerate(direction * 25.f);
        }
    }

    Command command;
    command.category = Category::Player;
    command.action = derivedAction<PlayerNode>([&](PlayerNode& player, sf::Time dt) 
    {
        mDuration += dt;
        if (mDuration >= sf::seconds(0.5f))
        {
            if (Utility::collision(*this, player))
                player.damageFromPos(1, SceneNode::getWorldPosition());
            mDuration = sf::Time::Zero;
        }
            
    });
    commands.push(command);

    mText->setString(std::to_string(Entity::getHitpoints()) + "HP");
}

void Enemy::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const 
{
    target.draw(mSprite, states);
}
