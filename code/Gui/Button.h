/** @file Button.h */
#pragma once

#include <functional>

#include "App/Context.h"

namespace GUI
{

class Button : public sf::Drawable, public sf::NonCopyable
{
    public:
        typedef std::function<void()> Callback;

        enum Type
        {
            Normal,
            Selected,
            Pressed,
            ButtonCount
        };
    public:
        Button(Context& context);
        void setCallback(Callback callback);
        void setText(const std::string& text); 
        void handleEvent(const sf::Event& event);
        void update(sf::Time);
        void setPosition(const sf::Vector2f& position);
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void changeTexture(Type buttonType);
    private:
        Callback mCallback;
        sf::Text mText;
        bool mIsSelected;
        bool mIsPressed;
        SoundPlayer& mSounds;
};

}