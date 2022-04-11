/** @file Button.cpp */
#include "Gui/Button.h"

namespace GUI
{

Button::Button(Context& context)
: mCallback()
, mIsSelected(false)
, mIsPressed(false)
, mContext(context)
{ 
    changeTexture(Normal);
}

void Button::setCallback(Callback callback)
{
    mCallback = std::move(callback);
}

void Button::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseMoved)
    {
        const auto& mouse = event.mouseMove;
        sf::Vector2f mousePos = mContext.window.mapPixelToCoords(sf::Vector2i(mouse.x, mouse.y)); 
        if (getGlobalBounds().contains(mousePos))
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
{ }

}