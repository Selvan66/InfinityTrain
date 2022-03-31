/** @file CommandQueue.h */
#pragma once

#include <queue>

#include "Objects/Command.h"

class CommandQueue 
{
    public:
        void push(const Command& command);
        Command pop();
        bool isEmpty() const;
    private:
        std::queue<Command> mQueue;
}