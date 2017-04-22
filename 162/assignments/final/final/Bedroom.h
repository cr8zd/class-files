/*****************************************************************************************
** Program Filename: Bedroom.h
** Author: Jennifer Frase
** Date: 3/17/15
** Description: creates a room where single item are hidden in certain places, such as
**              a bottle of pills in a desk
*****************************************************************************************/
#include <string>
#include <map>
#include "Room.h"
#include "Pack.h"

#ifndef BEDROOM_H_INCLUDED
#define BEDROOM_H_INCLUDED

class Bedroom : public Room
{
private:
    std::string underBed;
    std::string inDesk;
    std::string inCloset;

public:
    Bedroom() : Room("Bedroom")
    {
        underBed = "empty";
        inDesk = "empty";
        inCloset = "empty";
        nName = "bed";
        eName = "closet";
        wName = "desk";
    }

    Bedroom(std::string roomName, std::string bed,
            std::string desk, std::string closet) : Room(roomName)
    {
        inCloset = closet;
        underBed = bed;
        inDesk = desk;
        nName = "bed";
        eName = "closet";
        wName = "desk";
    }

    void describe(Pack& pockets);
    bool inFront(Pack&);
    bool left(Pack&);
    bool right(Pack&);
    bool inBack(Pack&);
};

#endif // BEDROOM_H_INCLUDED
