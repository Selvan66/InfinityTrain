/** @file Button.h */
#pragma once

#include <functional>

#include "Gui/Component.h"
#include "App/Context.h"
class Button : public Component
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
        
        virtual void handleEvent(const sf::Event& event) override;
        virtual void update() override;
    private:
        virtual sf::FloatRect getGlobalBounds() const = 0;
        virtual void changeTexture(Type buttonType);
    private:
        Callback mCallback;
        bool mIsSelected;
        bool mIsPressed;
        Context& mContext;
};