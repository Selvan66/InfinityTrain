/** @file Button.cpp */
#include "Gui/Button.h"
#include "Utils/Utility.h"


namespace GUI
{

Button::Button(Context& context)
: mCallback()
, mText("", context.fonts.get(FontsID::PixelFont))
, mIsSelected(false)
, mIsPressed(false)
, mSounds(context.sounds)
{
    mText.setOutlineThickness(1.f);
    mText.setOutlineColor(sf::Color(0, 0, 0));
    changeTexture(Normal);
}

void Button::setCallback(Callback callback)
{
    mCallback = std::move(callback);
}

void Button::setText(const std::string& text)
{
    mText.setString(text);
    Utility::centerOrigin(mText);
}

void Button::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseMoved)
    {
        const auto& mouse = event.mouseMove;
        sf::Vector2f mousePos = sf::Vector2f((float)mouse.x, (float)mouse.y); 
        if (mText.getGlobalBounds().contains(mousePos))
        {
            if (mIsSelected == false)
            {
                mSounds.play(SoundsID::ButtonHover);
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
            mSounds.play(SoundsID::ButtonClick);
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

void Button::setPosition(const sf::Vector2f& position)
{
    mText.setPosition(position);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mText, states);
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
    mText.setFillColor(color);
}

}