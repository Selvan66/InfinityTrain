/** TextSlideButton.cpp */
#include "Gui/TextSlideButton.h"

namespace GUI
{

TextSlideButton::TextSlideButton(Context& context)
: mContext(context)
, mLeft(context, 
    context.textures.get(TexturesID::ArrowButtons), 
    sf::IntRect(0, 0, 256, 256), 
    sf::IntRect(257, 0, 256, 256), 
    sf::IntRect(517, 0, 256, 256))
, mRight(context, 
    context.textures.get(TexturesID::ArrowButtons), 
    sf::IntRect(0, 0, 256, 256), 
    sf::IntRect(257, 0, 256, 256), 
    sf::IntRect(517, 0, 256, 256))
, mTextArray()
, mTextIndex(-1)
{
    mLeft.rotate(180);  
    mLeft.setScale(60.f / 256.f, 60.f / 256.f); 
    mLeft.setCallback(setPrevText);

    mRight.setScale(60.f / 256.f, 60.f / 256.f); 
    mRight.setCallback(setNextText);
}

void TextSlideButton::addText(const std::string& text)
{
    mTextArray.emplace_back(text, mContext.fonts.get(FontsID::PixelFont), 60);
    mTextIndex = 0;
}

void TextSlideButton::handleEvent(const sf::Event& event)
{
    mLeft.handleEvent(event);
    mRight.handleEvent(event);
}

void TextSlideButton::update(sf::Time dt)
{
    mLeft.update(dt);
    mRight.update(dt);   
}

void TextSlideButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= sf::Transformable::getTransform();
    if (mTextIndex != -1)
    {
        window.draw(mLeft);
        window.draw(mRight);
        window.draw(mTextArray[mTextIndex]);
    }
}

void TextSlideButton::setNextText()
{
    if (mTextIndex < mTextArray.size())
        ++mTextIndex;
}

void TextSlideButton::setPrevText()
{
    if (mTextIndex > 0)
        --mTextIndex;
}

}