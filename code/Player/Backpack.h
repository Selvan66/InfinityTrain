/** @file Backpack.h */
#pragma once

#include <array>
#include <queue>

#include "Player/Pocket.h"

class Backpack : public sf::Drawable, public sf::Transformable, public sf::NonCopyable
{
    public:
        Backpack(Context& context);

        void addItemToBackpack(std::unique_ptr<Pickup> item);
        void giveItemToDrop(size_t index);
        void drop(sf::Vector2f pos, SceneNode& node);

        void handleEvent(const sf::Event& event);
        void update();
        void setPosition(sf::Vector2f position);
    private:
        size_t getFirstFreeIndex() const;
        
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    private:
        static constexpr size_t mSize = 20;
        std::array<Pocket, mSize> mBackpack;
        std::queue<std::unique_ptr<Pickup>> mDropQueue;
};