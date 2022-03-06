#pragma once

#include <list>
#include <unordered_map>
#include <functional>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "App/Context.h"
#include "States/StatesID.h"
#include "States/State.h"

class StateStack : private sf::NonCopyable
{
    public:
        enum Action
        {
            Push,
            Pop,
            Clear
        };
    public:
        explicit StateStack(Context& context);
        template<typename T>
        void registerState(States::ID stateID);
        void update(sf::Time dt);
        void draw();
        void handleEvent(const sf::Event& event);
        void pushState(States::ID stateID);
        void popState();
        void clearState();
        bool isEmpty() const;
    private:
        State::Ptr createState(States::ID stateID);
        void applyPendingChanges();
    private:
        struct PendingChange
        {
            PendingChange(Action action, States::ID stateID = States::None);
            Action action;
            States::ID stateID;
        };
    private:
        std::list<State::Ptr> mStack;
        std::list<PendingChange> mPendingList;
        Context& mContext;
        std::unordered_map<States::ID, std::function<State::Ptr()>> mFactories;
};