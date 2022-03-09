/** @file PopupLabel.h */
#pragma once

#include "App/Context.h"

namespace GUI
{

class PopupLabel : public sf::Drawable, public sf::NonCopyable
{
    public:
        PopupLabel(Context& context, const sf::FloatRect& objectRect = sf::FloatRect(0.f, 0.f, 0.f, 0.f));
        void setText(const std::string& text);
        void setObjectRect(const sf::FloatRect& objectRect);
        void handleEvent(const sf::Event& event);
    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void setBackgoundRect();
        void setLabelPos(const sf::Vector2f& pos);
    private:
        sf::RectangleShape mBackground;
        bool mShow;
        sf::Text mText;
        sf::FloatRect mObjectRect;
};

}