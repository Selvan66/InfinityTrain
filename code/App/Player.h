/** @file Player.h */
#pragma once

#include <variant>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "Objects/CommandQueue.h"

class Player
{
    public:
        typedef std::variant<sf::Mouse::Button, sf::Keyboard::Key> Output;
    
        enum Action
        {
            MoveLeft,
            MoveRight,
            MoveUp,
            MoveDown,
            Fire,
            Interact,
            Special,
            ActionCount
        };
    
    public:
        Player();
    private:
        std::unordered_map<Output, Action> mKeyBinding;
        std::unordered_map<Action, Command> mActionBinding;  
};