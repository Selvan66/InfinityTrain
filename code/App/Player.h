/** @file Player.h */
#pragma once

#include <variant>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "Objects/CommandQueue.h"

struct Context;

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
        Player(Context& context);
        void loadPlayerInput();
        void handleEvent(const sf::Event& event, CommandQueue& commands);
        void handleRealtimeInput(CommandQueue& commands);
    private:
        void initializeActions();
        static bool isOutputPressed(Output key);
        static bool isRealtimeAction(Action action);
    private:
        Context& mContext;
        std::unordered_map<Output, Action> mKeyBinding;
        std::unordered_map<Action, Command> mActionBinding;  
};