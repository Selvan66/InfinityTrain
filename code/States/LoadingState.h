/** @file LoadingState.h */
#pragma once

#include "States/State.h"
#include "Utils/ParallelTask.h"
#include "Effects/Animation.h"

class LoadingState : public State
{
    public:
        LoadingState(StateStack& stack, Context& context);
        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event& event);
    private:
        void loadGameTexture();
    private:
        ParallelTask mTextureLoading;
        Animation mLoading;
};