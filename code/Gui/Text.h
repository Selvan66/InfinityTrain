/** @file Text.h */
#pragma once

#include "Gui/Component.h"
#include "App/Context.h"

class Text : public Component
{
    public:
        explicit Text(Context& context);
        void setString(const std::string& string);
        void setCharacterSize(unsigned int size);
    protected:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    private:
        sf::Text mText;
};