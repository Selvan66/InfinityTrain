/** @file GameState.cpp */
#include "States/GameState.h"

GameState::GameState(StateStack& stack, Context& context)
: State(stack, context)
, mMap(context)
{
    context.musics.play(MusicPlayer::Game);
    context.statistics.increase(Statistics::StartedGames);
}

void GameState::draw()
{ 
    mMap.draw();
}

bool GameState::update(sf::Time dt)
{
    auto& context = State::getContext();
    context.statistics.increase(Statistics::TimePlay, dt.asMilliseconds());

    mMap.draw();

    return true;  
}

bool GameState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        requestStackPush(StatesID::PauseState);
        
    return true;
}
