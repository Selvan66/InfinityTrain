/** @file Button.h */
#pragma once

#include <functional>

#include "App/Context.h"

namespace GUI
{

class Button : public sf::Text
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
    private:
        void changeTexture(Type buttonType);
    private:
        Callback mCallback;
        bool mIsSelected;
        bool mIsPressed;
        Context& mContext;
};

}