/** @file PopupLabel.h */
#pragma once

#include "App/Context.h"

class PopupLabel : public sf::Drawable, public sf::NonCopyable
{
    public:
        PopupLabel(Context& context, const sf::FloatRect& objectRect = sf::FloatRect(0.f, 0.f, 0.f, 0.f));
        void setText(const std::string& text);
        void setObjectRect(const sf::FloatRect& objectRect);
        void handleEvent(const sf::Event& event);
    private:
        void setBackgoundRect();
        void setLabelPos(const sf::Vector2f& pos);
        
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    private:
        sf::RectangleShape mBackground;
        bool mShow;
        sf::Text mText;
        sf::FloatRect mObjectRect;
        Context& mContext;
};