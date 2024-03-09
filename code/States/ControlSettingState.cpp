/** @file ControlSettingState.cpp */
#include "States/ControlSettingState.h"
#include "Gui/TextButton.h"

ControlSettingState::ControlSettingState(StateStack &stack, Context &context)
    : State(stack, context),
      mActionBinding(
          context.settings.get<std::unordered_map<std::string, std::string>>(
              "Control")) // It's stupid but works
      ,
      mActionToChange(""), mChange(false), mChangeBackground(),
      mChangeText("PRESS ANY KEY", context.fonts.get(FontsID::PixelFont), 90) {
  const sf::Vector2f &window_size = context.window.getView().getSize();
  mChangeBackground.setFillColor(sf::Color(0, 0, 0, 150));
  mChangeBackground.setSize(context.window.getView().getSize());

  Utility::centerOrigin(mChangeText);
  mChangeText.setOutlineThickness(2.f);
  mChangeText.setOutlineColor(sf::Color(0, 0, 0));
  mChangeText.setPosition(
      sf::Vector2f(window_size.x / 2.f, window_size.y / 2.f));

  State::loadGuiParser(GuiFileID::ControlSetting);
  applyGuiFunctions();
  updateTextOnButton();
}

void ControlSettingState::draw() {
  State::draw();

  auto &window = State::getContext().window;

  if (mChange) {
    window.draw(mChangeBackground);
    window.draw(mChangeText);
  }
}

bool ControlSettingState::update(sf::Time dt) {
  if (!mChange)
    State::update(dt);

  return true;
}

bool ControlSettingState::handleEvent(const sf::Event &event) {
  if (mChange) {
    if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::Escape) {
        mChange = false;
        mActionToChange = "";
        return true;
      }

      changeActionBinding(Utility::toString(event.key.code));
    } else if (event.type == sf::Event::MouseButtonPressed) {
      changeActionBinding(Utility::toString(event.mouseButton.button));
    }
  } else {
    State::handleEvent(event);
  }

  return true;
}

void ControlSettingState::applyGuiFunctions() {
  State::getGuiComponent<TextButton>("PlayerMoveUp").setCallback([&]() {
    mActionToChange = "Up";
    mChange = true;
  });

  State::getGuiComponent<TextButton>("PlayerMoveDown").setCallback([&]() {
    mActionToChange = "Down";
    mChange = true;
  });

  State::getGuiComponent<TextButton>("PlayerMoveLeft").setCallback([&]() {
    mActionToChange = "Left";
    mChange = true;
  });

  State::getGuiComponent<TextButton>("PlayerMoveRight").setCallback([&]() {
    mActionToChange = "Right";
    mChange = true;
  });

  State::getGuiComponent<TextButton>("PlayerFire").setCallback([&]() {
    mActionToChange = "Fire";
    mChange = true;
  });

  State::getGuiComponent<TextButton>("PlayerInteract").setCallback([&]() {
    mActionToChange = "Interact";
    mChange = true;
  });

  State::getGuiComponent<TextButton>("PlayerSpecial").setCallback([&]() {
    mActionToChange = "Special";
    mChange = true;
  });

  State::getGuiComponent<TextButton>("BackButton").setCallback([&]() {
    this->requestStackPop();
    this->requestStackPush(StatesID::SettingState);
  });

  auto &context = State::getContext();
  State::getGuiComponent<TextButton>("ApplySaveButton").setCallback([&]() {
    context.settings.set<std::unordered_map<std::string, std::string>>(
        mActionBinding, "Control");
    context.applyContolSettings();
  });
}

void ControlSettingState::updateTextOnButton() {
  State::getGuiComponent<TextButton>("PlayerMoveUp")
      .setText("Move Up: " + mActionBinding["Up"]);
  State::getGuiComponent<TextButton>("PlayerMoveDown")
      .setText("Move Down: " + mActionBinding["Down"]);
  State::getGuiComponent<TextButton>("PlayerMoveLeft")
      .setText("Move Left: " + mActionBinding["Left"]);
  State::getGuiComponent<TextButton>("PlayerMoveRight")
      .setText("Move Right: " + mActionBinding["Right"]);
  State::getGuiComponent<TextButton>("PlayerFire")
      .setText("Fire: " + mActionBinding["Fire"]);
  State::getGuiComponent<TextButton>("PlayerInteract")
      .setText("Interact: " + mActionBinding["Interact"]);
  State::getGuiComponent<TextButton>("PlayerSpecial")
      .setText("Special: " + mActionBinding["Special"]);
}

void ControlSettingState::changeActionBinding(std::string key) {
  auto found =
      std::find_if(mActionBinding.begin(), mActionBinding.end(),
                   [&key](const auto &pair) { return pair.second == key; });
  if (found != mActionBinding.end())
    found->second = Utility::toString(sf::Keyboard::Unknown);
  mActionBinding[mActionToChange] = key;
  mChange = false;
  updateTextOnButton();
  mActionToChange = "";
}