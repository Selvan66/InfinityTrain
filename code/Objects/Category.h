/** @file Category.h */
#pragma once

namespace Category
{

enum Type
{
    None = 0,
    Player = 1 << 0,
    Battlefield = 1 << 1,
    Floor = 1 << 2,
    Interactable = 1 << 3,
};

}