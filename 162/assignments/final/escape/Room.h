/*****************************************************************************************
** Program Filename: Room.h
** Author: Jennifer Frase
** Date: 3/17/15
** Description: class for the abstract room, that holds information on its walls
*****************************************************************************************/
#include <string>
#include <map>
#include "Pack.h"

#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

class Room
{
protected:
    std::string name,
                nName,
                sName,
                wName,
                eName;
    Room *north,
         *south,
         *west,
         *east;
    bool caught;
public:
    Room()
    {
        name = "";
        north = NULL;
        south = NULL;
        west = NULL;
        east = NULL;
        nName = "empty";
        sName = "empty";
        wName = "empty";
        eName = "empty";
        caught = false;
    }

    Room(std::string name)
    {
        this->name = name;
        north = NULL;
        south = NULL;
        west = NULL;
        east = NULL;
        nName = "wall";
        sName = "wall";
        wName = "wall";
        eName = "wall";
        caught = false;
    }

    /*allows for forewarning of guarded rooms, as well as spying*/
    virtual void peek(){};

    /*gives the description of the room*/
    virtual void describe(Pack&) = 0;

    /*function to execute action from that side of the wall
      front = north, left = west, back = south, right = east
      returns true if the wall has a door*/
    virtual bool inFront(Pack&)
    { return false; }
    virtual bool left(Pack&)
    { return false; }
    virtual bool right(Pack&)
    { return false; }
    virtual bool inBack(Pack&)
    { return false; }

    /*externally set the pointers and/or the wall names*/
    void setNorth(Room *next)
    { north = next; nName = next->getName();}

    void setNorth(std::string action)
    { nName = action; }

    void setSouth(Room *next)
    { south = next; sName = next->getName();}

    void setSouth(std::string action)
    { sName = action; }

    void setWest(Room *next)
    { west = next; wName = next->getName();}

    void setWest(std::string action)
    { wName = action; }

    void setEast(Room *next)
    { east = next; eName = next->getName();}

    void setEast(std::string action)
    { eName = action; }

    /*move in the direction by returning the appropriate pointer*/
    Room * goNorth()
    { return north; }

    Room * goSouth()
    { return south; }

    Room * goWest()
    { return west; }

    Room * goEast()
    { return east; }

    /*returns the room and wall names*/
    std::string getName()
    { return name; }

    std::string getNName()
    { return nName; }

    std::string getSName()
    { return sName; }

    std::string getWName()
    { return wName; }

    std::string getEName()
    { return eName; }

    bool isCaught()
    { return caught; }
};
#endif // ROOM_H_INCLUDED
