/*****************************************************************************************
** Program Filename: Portal.h
** Author: Jennifer Frase
** Date: 3/17/15
** Description: less strict version of Guarded, where you can pass if you have a specific
**              item in inventory
*****************************************************************************************/
#include <string>
#include <map>
#include "Room.h"
#include "Guarded.h"
#include "Pack.h"

#ifndef PORTAL_H_INCLUDED
#define PORTAL_H_INCLUDED

class Portal : public Guarded
{
public:

    Portal() : Guarded("Portal", "medicated ham and swiss"){};

    void peek()
    {
        std::cout << "\nYou hear voices coming from the room."
                  << "\n\"You deserve it and you know it\""
                  << "\n\"What could I do, Ralph was hungry.\""
                  << "\n\"Yes, it was the dog that was hungry...\""
                  << "\n\"Well, it was...\""
                  << "\n\"It doesn't matter who was hungry, you stole"
                  << " the food. So now YOU have to guard the door.\""
                  << "\n\"...Could you at least send some food for the dog?\""
                  << "\n\"And let me guess, you want sandwiches...\""
                  << "\n..."
                  << "\n\"Yeah, definitely for the dog.\""
                  << "\n\"If your not going to get me food, then leave, I've"
                  << " got a door to guard.\""
                  << std::endl;
    }


    /*****************************************************************************************
    ** Function: describe
    ** Description: enters the room and checks your inventory for the required item
    ** Parameters: the inventory
    ** Pre-Conditions: inventory must be size 7
    ** Post-Conditions: none
    *****************************************************************************************/
    void describe(Pack& pockets)
    {
        std::cout << "\nTo the east is the portal home, and to west is "
                  <<  wName << "\nand to the north is the guard's"
                  << "desk." << std::endl;

        bool there = false;
        for(int i = 0; i < 7; i++)
        {
            if(pockets[i].name == getNeed())
            {
                there = true;
                pockets.removeItem(pockets[i]);
            }
        }
        if(there)
        {
            std::cout << "\nThe guard and dog are sound asleep after eating the"
                      << "\nthe sandwich you brought. They never even bothered to"
                      << "\nlook at you. If it hadn't been such a success, you"
                      << "\nmight feel self-conscious about it."
                      << std::endl;
        }
    }

    bool right(Pack& pockets)
    {
        return true;
    }

    bool left(Pack& pockets)
    {
        return true;
    }
};

#endif // PORTAL_H_INCLUDED
