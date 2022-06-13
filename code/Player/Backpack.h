/** @file Backpack.h */
#pragma once

#include <array>
#include <queue>

#include "Objects/Nodes/Pickup.h"

class Backpack : public sf::Drawable, public sf::Transformable, public sf::NonCopyable
{
    public:
        Backpack();

        void addItemToBackpack(std::unique_ptr<Pickup> item);
        void giveItemToDrop(size_t index);
        void drop(sf::Vector2f pos, SceneNode& node);
    private:
        size_t getFirstFreeIndex() const;
        
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    private:
        static constexpr size_t mSize = 20;
        std::array<std::unique_ptr<Pickup>, mSize> mBackpack;
        std::queue<std::unique_ptr<Pickup>> mDropQueue;
};