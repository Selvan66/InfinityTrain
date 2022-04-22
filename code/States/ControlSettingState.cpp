/** @file ControlSettingState.cpp */
#include "States/ControlSettingState.h"
#include "Utils/Utility.h"

ControlSettingState::ControlSettingState(StateStack& stack, Context& context)
: State(stack, context)
, mActionBinding(context.settings.get<std::unordered_map<std::string, std::string>>("Control"))
, mControlButton{context, context, context, context, context, context, context}      // It's stupid but works
, mActionToChange("")
, mChange(false)
, mChangeBackground()
, mChangeText("PRESS ANY KEY", context.fonts.get(FontsID::PixelFont), 90)
, mOptionButton()
{
    createGUI();
    updateTextOnButton();
}

void ControlSettingState::draw()
{
    auto& window = State::getContext().window;
    
    for (auto& button : mControlButton)
        window.draw(button);

    for (auto& button : mOptionButton)
        window.draw(button);
    
    if (mChange)
    {
        window.draw(mChangeBackground);
        window.draw(mChangeText);
    }
}

bool ControlSettingState::update(sf::Time dt)
{
    if (!mChange) 
    {
        for (auto& button : mControlButton)
            button.update(dt);

        for (auto& button : mOptionButton)
            button.update(dt);
    }

    return true;
}

bool ControlSettingState::handleEvent(const sf::Event& event)
{
    if (mChange)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                mChange = false;
                mActionToChange = "";
                return true;
            }

            changeAction(Utility::toString(event.key.code));
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            changeAction(Utility::toString(event.mouseButton.button));
        }
    }
    else 
    {
        for (auto& button : mControlButton)
            button.handleEvent(event);

        for (auto& button : mOptionButton)
            button.handleEvent(event);
    }
    
    
    return true;
}

void ControlSettingState::createGUI()
{
    auto& context = State::getContext();
    const sf::Vector2f& windowSize = context.window.getView().getSize();
    const float textPadding = 100.f;

    mChangeBackground.setFillColor(sf::Color(0, 0, 0, 150));
    mChangeBackground.setSize(context.window.getView().getSize());

    Utility::centerOrigin(mChangeText);
    mChangeText.setOutlineThickness(2.f);
	mChangeText.setOutlineColor(sf::Color(0, 0, 0));
    mChangeText.setPosition(sf::Vector2f(windowSize.x / 2.f, windowSize.y / 2.f));

    mControlButton[Player::MoveUp].setPosition(sf::Vector2f(windowSize.x * 2.f / 7.f, (windowSize.y / 2.f) - (1 * textPadding)));
    mControlButton[Player::MoveUp].setCallback([&]()
    {
        mActionToChange = "Up";
        mChange = true;
    });

    mControlButton[Player::MoveDown].setPosition(sf::Vector2f(windowSize.x * 2.f / 7.f, (windowSize.y / 2.f) - (0 * textPadding)));
    mControlButton[Player::MoveDown].setCallback([&]()
    {
        mActionToChange = "Down";
        mChange = true;
    });

    mControlButton[Player::MoveLeft].setPosition(sf::Vector2f(windowSize.x * 2.f / 7.f, (windowSize.y / 2.f) + (1 * textPadding)));
    mControlButton[Player::MoveLeft].setCallback([&]()
    {
        mActionToChange = "Left";
        mChange = true;
    });

    mControlButton[Player::MoveRight].setPosition(sf::Vector2f(windowSize.x * 2.f / 7.f, (windowSize.y / 2.f) + (2 * textPadding)));
    mControlButton[Player::MoveRight].setCallback([&]()
    {
        mActionToChange = "Right";
        mChange = true;
    });

    mControlButton[Player::Fire].setPosition(sf::Vector2f(windowSize.x * 5.f / 7.f, (windowSize.y / 2.f) - (1 * textPadding)));
    mControlButton[Player::Fire].setCallback([&]()
    {
        mActionToChange = "Fire";
        mChange = true;
    });

    mControlButton[Player::Interact].setPosition(sf::Vector2f(windowSize.x * 5.f / 7.f, (windowSize.y / 2.f) - (0 * textPadding)));
    mControlButton[Player::Interact].setCallback([&]()
    {
        mActionToChange = "Interact";
        mChange = true;
    });

    mControlButton[Player::Special].setPosition(sf::Vector2f(windowSize.x * 5.f / 7.f, (windowSize.y / 2.f) + (1 * textPadding)));
    mControlButton[Player::Special].setCallback([&]()
    {
        mActionToChange = "Special";
        mChange = true;
    });

    mOptionButton.emplace_back(context);
    auto& backButton = mOptionButton.back();
    backButton.setText("BACK");
    backButton.setPosition(sf::Vector2f(windowSize.x / 3.f, windowSize.y * 4.f / 5.f));
    backButton.setCallback([&]()
    {
        this->requestStackPop();
        this->requestStackPush(StatesID::SettingState);
    });


    mOptionButton.emplace_back(context);
    auto& saveButton = mOptionButton.back();
    saveButton.setText("APPLY & SAVE");
    saveButton.setPosition(sf::Vector2f(windowSize.x * 2.f / 3.f, windowSize.y * 4.f / 5.f));
    saveButton.setCallback([&]()
    {
        context.settings.set<std::unordered_map<std::string, std::string>>(mActionBinding, "Control");
        context.applyContolSettings();
    });
}

void ControlSettingState::updateTextOnButton()
{
    auto& settings = State::getContext().settings;
    mControlButton[Player::MoveUp].setText("Move Up: " + mActionBinding["Up"]);
    mControlButton[Player::MoveDown].setText("Move Down: " + mActionBinding["Down"]);
    mControlButton[Player::MoveLeft].setText("Move Left: " + mActionBinding["Left"]);
    mControlButton[Player::MoveRight].setText("Move Right: " + mActionBinding["Right"]);
    mControlButton[Player::Fire].setText("Fire: " + mActionBinding["Fire"]);
    mControlButton[Player::Interact].setText("Interact: " + mActionBinding["Interact"]);
    mControlButton[Player::Special].setText("Special: " + mActionBinding["Special"]);
}

void ControlSettingState::changeAction(std::string key)
{
    auto& found = std::find_if(mActionBinding.begin(), mActionBinding.end(), 
                [&](auto& pair){ return pair.second == key; });
    if (found != mActionBinding.end())
        found->second = Utility::toString(sf::Keyboard::Unknown);
    mActionBinding[mActionToChange] = key;
    mChange = false;
    updateTextOnButton();
    mActionToChange = "";
}
