/*****************************************************************************************
** Program Filename: Guarded.h
** Author: Jennifer Frase
** Date: 3/17/15
** Description: creates a room that has a high chance of getting caught in. THe default
**              is 100% catch rate. and as a result, there are no links leaving the room.
*****************************************************************************************/
#include <string>
#include <map>
#include "Room.h"
#include "Pack.h"

#ifndef GUARDED_H_INCLUDED
#define GUARDED_H_INCLUDED

class Guarded : public Room
{
private:
    std::string needs;
public:

    Guarded() : Room("Guarded")
    { needs = ""; }

    Guarded(std::string name) : Room(name)
    { needs = ""; }

    Guarded(std::string name, std::string needed) : Room(name)
    { needs = needed; }

    void peek()
    {
        std::cout << "\nGetting close to the door you hear voices coming from the"
                  << "room.\nYou immediately second guess entering the room."
                  << std::endl;
    }

    void describe(Pack& pockets)
    {
        std::cout << "\nYou enter the room and the people inside turn to look at you."
                  << "\nYou have been caught." << std::endl;
        caught = true;
    }

    std::string getNeed()
    { return needs; }
};


#endif // GUARDED_H_INCLUDED
