/** @file Enemy.cpp */
#pragma once

#include "Objects/Nodes/Enemy.h"


Enemy::Enemy(Context& context)
: Entity(100)
, mSprite(context.textures.get(TexturesID::Player), {0, 0, 80, 61})
, mPlayer(nullptr)
{
    
}

void Enemy::updateCurrent(sf::Time dt, CommandQueue& commands)
{
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
        sf::Vector2f direction = mPlayer->getPosition() - getPosition();
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > 0.f)
        {
            direction /= length;
            Entity::move(direction * 100.f * dt.asSeconds());
        }
    }
}

void Enemy::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const 
{
    target.draw(mSprite, states);
}
