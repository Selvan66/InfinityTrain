/** @file Backpack.cpp */
#include "Player/Backpack.h"

Backpack::Backpack()
: mBackpack()
, mDropQueue()
{
    for (int i = 0; i < mSize; ++i)
        mBackpack[i] = std::unique_ptr<Pickup>(nullptr);
}

void Backpack::addItemToBackpack(std::unique_ptr<Pickup> item)
{
    size_t index = getFirstFreeIndex();
    
    if (index == -1)
    {
        giveItemToDrop(0);
        index = 0;
    }
    
    mBackpack[index] = std::move(item);
}

void Backpack::giveItemToDrop(size_t index)
{
    if (mBackpack[index].get() == nullptr)
        return;
    mDropQueue.push(std::move(mBackpack[index]));
    mBackpack[index] = std::unique_ptr<Pickup>(nullptr);
}

void Backpack::drop(sf::Vector2f pos, SceneNode& node)
{
    Command command;
    command.category = Category::Floor;
    while (!mDropQueue.empty())
    {
        mDropQueue.back()->setPosition(pos);
        node.attachChild(std::move(mDropQueue.back()));
        mDropQueue.pop();
    }
}

size_t Backpack::getFirstFreeIndex() const
{
    for (size_t i = 0; i < mSize; ++i)
        if (mBackpack[i].get() == nullptr)
            return i;
    return -1;
}

void Backpack::draw(sf::RenderTarget &target, sf::RenderStates states) const 
{
    // ...
}