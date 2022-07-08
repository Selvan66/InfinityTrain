/** @file Button.cpp */
#include "Gui/Button.h"

Button::Button(Context& context)
: Component()
, mLeftClickCallback()
, mRightClickCallback()
, mIsSelected(false)
, mIsPressed(false)
, mContext(context)
{ 
    changeTexture(Normal);
}

void Button::setCallback(Callback callback)
{
    setLeftClickCallback(callback);
    setRightClickCallback(callback);
}

void Button::setLeftClickCallback(Callback callback)
{
    mLeftClickCallback = std::move(callback);
}

void Button::setRightClickCallback(Callback callback)
{
    mRightClickCallback = std::move(callback);
}

void Button::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseMoved)
    {
        const auto& mouse = event.mouseMove;
        sf::Vector2f mousePos = mContext.window.mapPixelToCoords(sf::Vector2i(mouse.x, mouse.y)); 
        if (getGlobalBounds().contains(mousePos))
        {
            if (!mIsSelected)
                mContext.sounds.play(SoundsID::ButtonHover);
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
    if (event.type == sf::Event::MouseButtonReleased)
    {
        if (mIsPressed && mIsSelected && event.mouseButton.button == sf::Mouse::Right)
            mRightClickCallback();
        if (mIsPressed && mIsSelected && event.mouseButton.button == sf::Mouse::Left)
            mLeftClickCallback();
        

        mIsPressed = false;
    }
}

void Button::update()
{
    if (mIsSelected)
        changeTexture(Selected);
    if (mIsPressed)
        changeTexture(Pressed);
    if (!mIsPressed && !mIsSelected)
        changeTexture(Normal);
}

void Button::changeTexture(Type buttonType)
{ }