/** @file TextSlider.cpp */
#include "Gui/TextSlider.h"
#include "Utils/Utility.h"
#include "Utils/Exceptions/bad_argument.h"

TextSlider::TextSlider(Context& context)
: mContext(context)
, mLeft(context)
, mRight(context)
, mTextArray()
, mTextIndex(-1)
, mMaxTextWidth(0)
{
    mLeft.setTextures(context.textures.get(TexturesID::ArrowButtons), 
                    sf::IntRect(0, 0, 256, 256), 
                    sf::IntRect(257, 0, 256, 256), 
                    sf::IntRect(517, 0, 256, 256));
    
    mLeft.rotate(180);  
    mLeft.setScale(60.f / 256.f, 60.f / 256.f); 
    mLeft.setCallback([this](){this->setPrevText();});
    
    
    mRight.setTextures(context.textures.get(TexturesID::ArrowButtons), 
                    sf::IntRect(0, 0, 256, 256), 
                    sf::IntRect(257, 0, 256, 256), 
                    sf::IntRect(517, 0, 256, 256));
                    
    mRight.setScale(60.f / 256.f, 60.f / 256.f); 
    mRight.setCallback([this](){this->setNextText();});
}

void TextSlider::addText(const std::string& text)
{
    sf::Text newText(text, mContext.fonts.get(FontsID::PixelFont), 50);
    newText.setOutlineThickness(2.f);
    newText.setOutlineColor(sf::Color(0, 0, 0));
    Utility::centerOrigin(newText);
    float width = newText.getGlobalBounds().width;
    mMaxTextWidth = width > mMaxTextWidth ? width : mMaxTextWidth;
    mTextArray.push_back(newText);
    mTextIndex = 0;
}

std::string TextSlider::getCurrentText() const
{
    assert(mTextIndex != -1);
    return mTextArray[mTextIndex].getString();
}

void TextSlider::setCurrentText(const std::string& text)
{
    assert(mTextIndex != -1);
    for (int i = 0; i < mTextArray.size(); ++i)
    {
        if (mTextArray[i].getString() == text)
        {
            mTextIndex = i;
            return;
        }
    }
    
    throw Except::bad_argument().add("Text Slider").add("Not found text in mTextArray");
}

// Apply after addText()
void TextSlider::setPosition(const sf::Vector2f& pos)
{
    mLeft.setPosition(-mMaxTextWidth / 1.5f, 0);
    mRight.setPosition(mMaxTextWidth / 1.5f, 0);
    mLeft.move(pos);
    mRight.move(pos);
}

void TextSlider::handleEvent(const sf::Event& event)
{
    mLeft.handleEvent(event);
    mRight.handleEvent(event);
}

void TextSlider::update()
{
    mLeft.update();
    mRight.update();   

    setPosition(sf::Transformable::getPosition());
}

void TextSlider::setNextText()
{
    if (mTextIndex < (mTextArray.size() - 1))
        ++mTextIndex;
}

void TextSlider::setPrevText()
{
    if (mTextIndex > 0)
        --mTextIndex;
}

void TextSlider::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= sf::Transformable::getTransform();
    if (mTextIndex != -1)
    {
        target.draw(mLeft);
        target.draw(mRight);
        target.draw(mTextArray[mTextIndex], states);
    }
}