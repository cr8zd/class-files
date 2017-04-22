/*****************************************************************************************
** Program Filename: Food.h
** Author: Jennifer Frase
** Date: 3/17/15
** Description: class that stores information on heavy list items, such as the large
**              table, where the user can interact with it
*****************************************************************************************/
#include <string>
#include <map>
#include "Room.h"
#include "Pack.h"

#ifndef FOOD_H_INCLUDED
#define FOOD_H_INCLUDED

class Food : public Room
{
private:
    Pack table; //large array of Items

public:
    Food() : Room("Food")
    { table.setLimit(15); sName = "table"; wName = "dinnerware"; }

    Food(std::string name) : Room(name)
    {sName = "table"; wName = "dinnerware"; }

    void describe(Pack& pockets);
    bool inFront(Pack& pockets);
    bool left(Pack& pockets);
    bool right(Pack& pockets);
    bool inBack(Pack& pockets);
};

#endif // FOOD_H_INCLUDED
