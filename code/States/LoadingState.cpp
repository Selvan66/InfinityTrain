/** @file LoadingState.cpp */
#include "States/LoadingState.h"

bool LoadingState::loaded = false;

LoadingState::LoadingState(StateStack& stack, Context& context)
: State(stack, context)
, mTextureLoading(loaded ? std::function<bool()>([](){return true;}) : std::function<bool()>([this](){this->loadGameTexture(); return true;}))
, mLoading(context.textures.get(TexturesID::Loading))
{
    mLoading.setDuration(sf::seconds(1));
    mLoading.setFrameSize({200, 200});
    mLoading.setNumFrames(30);
    mLoading.setRepeating(true);
    mLoading.setPosition({1650, 850});
}

void LoadingState::draw()
{
    auto& context = State::getContext();
    context.window.draw(mLoading);
}

bool LoadingState::update(sf::Time dt)
{
    mLoading.update(dt);

    if (mTextureLoading.isFinished())
    {
        loaded = true;
        requestStackPop();
        requestStackPush(StatesID::GameState);
    }

    return true;
}

bool LoadingState::handleEvent(const sf::Event& event)
{
    return true;
}

void LoadingState::loadGameTexture()
{
    auto& context = State::getContext();
    context.textures.load(TexturesID::DefaultLevel, "image/defaultLevel.png");
    context.textures.load(TexturesID::PrehistoryLevel, "image/prehistoryLevel.png");
    context.textures.load(TexturesID::Player, "image/player1.png");
    context.textures.load(TexturesID::Money, "image/money.png");
    context.textures.load(TexturesID::Heart, "image/heart.png");
}
