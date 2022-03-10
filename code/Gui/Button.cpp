/** @file Button.cpp */
#include "Gui/Button.h"
#include "Utils/Utility.h"


namespace GUI
{

Button::Button(Context& context)
: sf::Text("", context.fonts.get(FontsID::PixelFont), 60)
, mCallback()
, mIsSelected(false)
, mIsPressed(false)
, mContext(context)
{
    sf::Text::setOutlineThickness(2.f);
    sf::Text::setOutlineColor(sf::Color(0, 0, 0));
    changeTexture(Normal);
}

void Button::setCallback(Callback callback)
{
    mCallback = std::move(callback);
}

void Button::setText(const std::string& text)
{
    sf::Text::setString(text);
    Utility::centerOrigin(*this);
}

void Button::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseMoved)
    {
        const auto& mouse = event.mouseMove;
        sf::Vector2f mousePos = mContext.window.mapPixelToCoords(sf::Vector2i(mouse.x, mouse.y)); 
        if (sf::Text::getGlobalBounds().contains(mousePos))
        {
            if (mIsSelected == false)
            {
                mContext.sounds.play(SoundsID::ButtonHover);
            }
            mIsSelected = true;
        }
        else
        {
            mIsSelected = false;
        }
    }
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (mIsSelected)
        {
            mIsPressed = true;
            mContext.sounds.play(SoundsID::ButtonClick);
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased)
    {
        if (mIsPressed && mIsSelected)
        {
            mCallback();
        }

        mIsPressed = false;
    }
}

void Button::update(sf::Time)
{
    if (mIsSelected)
    {
        changeTexture(Selected);
    }
    if (mIsPressed)
    {
        changeTexture(Pressed);
    }
    if (!mIsPressed && !mIsSelected)
    {
        changeTexture(Normal);
    }
}

void Button::changeTexture(Type buttonType)
{
    sf::Color color;
    switch (buttonType)
    {
        case Normal:
            color = sf::Color(255, 255, 255);
            break;
        case Selected:
            color = sf::Color(255, 80, 80);
            break;
        case Pressed:
            color = sf::Color(255, 0, 0);
            break;
    }
    sf::Text::setFillColor(color);
}

}