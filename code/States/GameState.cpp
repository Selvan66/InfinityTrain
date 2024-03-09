/** @file GameState.cpp */
#include "States/GameState.h"

GameState::GameState(StateStack &stack, Context &context)
    : State(stack, context), mMap(context) {
  context.musics.play(MusicPlayer::Game);
  context.statistics.increase(Statistics::StartedGames);
}

void GameState::draw() { mMap.draw(); }

bool GameState::update(sf::Time dt) {
  if (mMap.isPlayerAlive())
    mMap.update(dt);
  else
    requestStackPush(StatesID::GameOverState);

  return true;
}

bool GameState::handleEvent(const sf::Event &event) {
  if ((event.type == sf::Event::KeyPressed &&
       event.key.code == sf::Keyboard::Escape) ||
      event.type == sf::Event::LostFocus)
    requestStackPush(StatesID::PauseState);

  mMap.handleEvent(event);
  return true;
}