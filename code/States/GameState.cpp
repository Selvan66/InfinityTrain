/** @file GameState.cpp */
#include "States/GameState.h"

GameState::GameState(StateStack& stack, Context& context)
: State(stack, context)
{
    context.musics.play(MusicPlayer::Game);
}

void GameState::draw()
{ }

bool GameState::update(sf::Time dt)
{
    return true;  
}

bool GameState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        requestStackPush(StatesID::PauseState);
        
    return true;
}
