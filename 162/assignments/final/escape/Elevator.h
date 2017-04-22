/*****************************************************************************************
** Program Filename: Elevator.h
** Author: Jennifer Frase
** Date: 3/17/15
** Description: a version of Hall that connects Hall's together
*****************************************************************************************/
#include <iostream>
#include <string>
#include <map>
#include "Room.h"
#include "Pack.h"
#include "Hall.h"

#ifndef ELEVATOR_H_INCLUDED
#define ELEVATOR_H_INCLUDED

class Elevator : public Hall
{
public:
    Elevator() : Hall("Elevator"){};

    void describe(Pack& pockets)
    {
        std::cout << "\nYou have entered the elevator."
                  << std::endl;
    }

    bool left(Pack& pockets)
    { return false; }
};

#endif // ELEVATOR_H_INCLUDED
