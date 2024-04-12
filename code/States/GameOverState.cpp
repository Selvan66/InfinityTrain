/** @file GameOverState.cpp */
#include "spdlog/spdlog.h"

#include "States/GameOverState.h"

GameOverState::GameOverState(StateStack& stack, Context& context)
  : State(stack, context), mElapsedTime(sf::Time::Zero), mBackgroundShape() {
  mBackgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
  mBackgroundShape.setSize(context.window.getView().getSize());

  State::loadGuiParser(GuiFileID::GameOver);
  spdlog::info("GameOverState::GameOverState | GameOver State created");
}

void GameOverState::draw() {
  auto& window = State::getContext().window;
  window.draw(mBackgroundShape);

  State::draw();
}

bool GameOverState::update(sf::Time dt) {
  mElapsedTime += dt;
  if (mElapsedTime >= sf::seconds(3.f)) {
    requestStackClear();
    requestStackPush(StatesID::MenuState);
  }

  State::update(dt);
  return false;
}

bool GameOverState::handleEvent(const sf::Event& event) {
  State::handleEvent(event);
  return false;
}
