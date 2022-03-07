/** @file PopupLabel.h */
#pragma once

#include "Utils/ResourceIdentifiers.h"

namespace GUI
{

class PopupLabel : public sf::Drawable, public sf::Transformable, public sf::NonCopyable
{
    public:
        typedef std::shared_ptr<PopupLabel> Ptr;
    public:
        PopupLabel(const std::string& text, const FontHolder& fonts);
        void checkPopup(const sf::FloatRect& objectBounds, const sf::Vector2f& mousePos);
    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void setLabelPos(const sf::Vector2f& pos);
    private:
        sf::RectangleShape mBackground;
        bool mShow;
        sf::Text mText;
};

}