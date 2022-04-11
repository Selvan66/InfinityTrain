/** @file Button.h */
#pragma once

#include <functional>

#include "App/Context.h"

namespace GUI
{

class Button : public sf::Drawable, public sf::Transformable, public sf::NonCopyable
{
    public:
        typedef std::function<void()> Callback;

        enum Type
        {
            Normal,
            Selected,
            Pressed
        };
    public:
        Button(Context& context);
        void setCallback(Callback callback);
        void handleEvent(const sf::Event& event);
        void update(sf::Time);
    private:
        virtual sf::FloatRect getGlobalBounds() const = 0;
        virtual void changeTexture(Type buttonType);
    private:
        Callback mCallback;
        bool mIsSelected;
        bool mIsPressed;
        Context& mContext;
};

}