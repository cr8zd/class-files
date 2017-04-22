/*****************************************************************************************
** Program Filename: Hall.h
** Author: Jennifer Frase
** Date: 3/17/15
** Description: mostly used to connect a room to multiple other room.
*****************************************************************************************/
#include <iostream>
#include <string>
#include <map>
#include "Room.h"
#include "Pack.h"

#ifndef HALL_H_INCLUDED
#define HALL_H_INCLUDED

class Hall : public Room
{
public:

    Hall() : Room("Hall") {};

    Hall(std::string name) : Room(name){};

    void describe(Pack& pockets)
    {
        std::cout << "\nYou have entered a hall. To the west is an elevator,"
                  << "\nto the east, north, and/or south are doors."
                  << std::endl;
    }
    bool inFront(Pack& pockets)
    { return true; }
    bool left(Pack& pockets)
    { return true; }
    bool right(Pack& pockets)
    { return true; }
    bool inBack(Pack& pockets)
    { return true; }
};

#endif // HALL_H_INCLUDED
