/** @file Backpack.cpp */
#include "Player/Backpack.h"

#include <iostream> //< for debug

Backpack::Backpack(Context& context)
: mBackpack
{context, context, context, context, context, 
context, context, context, context, context, 
context, context, context, context, context, 
context, context, context, context, context}
, mDropQueue()
{
    for (int i = 0; i < mSize; ++i)
        mBackpack[i].setLeftClickCallback([this](){std::cout << "TEST" << std::endl;});
    
    for (int i = 0; i < mSize; ++i)
        mBackpack[i].setRightClickCallback([this, i](){this->giveItemToDrop(i);});

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 5; ++j)
            mBackpack[i * 5 + j].setPosition((j * 40.f), (i * 40.f));
}

void Backpack::addItemToBackpack(std::unique_ptr<Pickup> item)
{
    size_t index = getFirstFreeIndex();
    
    if (index == -1)
    {
        giveItemToDrop(0);
        index = 0;
    }
    
    mBackpack[index].addItem(std::move(item));
}

void Backpack::giveItemToDrop(size_t index)
{
    if (!mBackpack[index].isItem())
        return;
    mDropQueue.push(std::move(mBackpack[index].dropItem()));
}

void Backpack::drop(sf::Vector2f pos, SceneNode& node)
{
    Command command;
    command.category = Category::Floor;
    while (!mDropQueue.empty())
    {
        mDropQueue.front()->setPosition(pos);
        node.attachChild(std::move(mDropQueue.front()));
        mDropQueue.pop();
    }
}

void Backpack::handleEvent(const sf::Event& event)
{
    for (int i = 0; i < mSize; ++i)
        mBackpack[i].handleEvent(event);
}

void Backpack::update()
{
    for (int i = 0; i < mSize; ++i)
        mBackpack[i].update();
}

void Backpack::setPosition(sf::Vector2f position)
{
    for (int i = 0; i < mSize; ++i)
        mBackpack[i].move(position);
}

size_t Backpack::getFirstFreeIndex() const
{
    for (size_t i = 0; i < mSize; ++i)
        if (!mBackpack[i].isItem())
            return i;
    return -1;
}

void Backpack::draw(sf::RenderTarget &target, sf::RenderStates states) const 
{
    states.transform *= sf::Transformable::getTransform();
    for (int i = 0; i < mSize; ++i)
        target.draw(mBackpack[i], states);
}