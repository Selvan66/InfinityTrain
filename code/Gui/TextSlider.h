/** @file TextSlider.h */
#pragma once

#include <vector>

#include "Gui/TextureButton.h"

namespace GUI
{

class TextSlider : public sf::Drawable, public sf::Transformable, public sf::NonCopyable
{
    public:
        TextSlider(Context& context);
        void addText(const std::string& text);
        void handleEvent(const sf::Event& event);
        void update(sf::Time dt);
        std::string getCurrentText() const;
        void setPosition(float x, float y);
    private:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        void setNextText();
        void setPrevText();
    private:
        Context& mContext;
        TextureButton mLeft;
        TextureButton mRight;
        std::vector<sf::Text> mTextArray;
        int mTextIndex;
        float mMaxTextWidth;
};

}
