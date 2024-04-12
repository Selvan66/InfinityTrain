/** @file MenuState.cpp */
#include "spdlog/spdlog.h"

#include "States/MenuState.h"

MenuState::MenuState(StateStack& stack, Context& context)
  : State(stack, context), mBackgroundSprite(), mTitle() {
  const sf::Vector2f& window_size = context.window.getView().getSize();

  mBackgroundSprite.setTexture(context.textures.get(TexturesID::TitleScreen));

  mTitle.setFont(context.fonts.get(FontsID::PixelFont));
  mTitle.setString("INFINITY TRAIN");
  mTitle.setCharacterSize(120);
  mTitle.setOutlineThickness(2.f);
  mTitle.setOutlineColor(sf::Color(0, 0, 0));
  Utility::centerOrigin(mTitle);
  mTitle.setPosition(sf::Vector2f(window_size.x / 2.f, window_size.y / 5.f));

  context.musics.play(MusicPlayer::Menu);

  requestStackPush(StatesID::MenuOptionsState);

  spdlog::info("MenuState::MenuState | Menu State created");
}

void MenuState::draw() {
  auto& window = State::getContext().window;
  window.draw(mBackgroundSprite);
  window.draw(mTitle);
}
