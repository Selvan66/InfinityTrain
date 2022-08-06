/** @file LoadingState.cpp */
#include "States/LoadingState.h"

bool LoadingState::loaded = false;

LoadingState::LoadingState(StateStack& stack, Context& context)
: State(stack, context)
, mTexturesLoading(loaded ? std::function<bool()>([](){return true;}) : std::function<bool()>([this](){this->loadGameTextures(); return true;}))
, mGuiFilesLoading(loaded ? std::function<bool()>([](){return true;}) : std::function<bool()>([this](){this->loadGameGuiFiles(); return true;}))
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

    if (mTexturesLoading.isFinished() && mGuiFilesLoading.isFinished())
    {
        loaded = true;
        requestStackPop();
        requestStackPush(StatesID::GameState);
    }

    return true;
}

void LoadingState::loadGameGuiFiles()
{
    auto& context = State::getContext();
	context.gui.load(GuiFileID::Stats, "gui/Stats.gui");
    context.gui.load(GuiFileID::Map, "gui/Map.gui");
}

void LoadingState::loadGameTextures()
{
    auto& context = State::getContext();
    context.textures.load(TexturesID::DefaultLevel, "image/defaultLevel.png");
    context.textures.load(TexturesID::PrehistoryLevel, "image/prehistoryLevel.png");
    context.textures.load(TexturesID::StartLevel, "image/StartLevel.png");
    context.textures.load(TexturesID::FirstLevel, "image/FirstLevel.png");
    context.textures.load(TexturesID::Player, "image/player.png");
    context.textures.load(TexturesID::Money, "image/money.png");
    context.textures.load(TexturesID::Heart, "image/heart.png");
    context.textures.load(TexturesID::Potion, "image/potion.png");
    context.textures.load(TexturesID::Door, "image/doors.png");
}