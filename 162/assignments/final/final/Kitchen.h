/*****************************************************************************************
** Program Filename: Kitchen.h
** Author: Jennifer Frase
** Date: 3/17/15
** Description: more advanced version of Food, has multilpe large list interactions
                such as the fridge and pantry
*****************************************************************************************/
#include <iostream>
#include <string>
#include <map>
#include <ctime>
#include "Room.h"
#include "Food.h"
#include "Pack.h"

#ifndef KITCHEN_H_INCLUDED
#define KITCHEN_H_INCLUDED

class Kitchen : public Food
{
public:
    Kitchen() : Food("Kitchen")
    { nName = "fridge";
      eName = "pantry";
      sName = "table"; }

    void describe(Pack& pockets)
    {
        std::cout << "\nYou have enter the kitchens. To the north are"
                  << "\nfridges and to the east are the prep tables. There"
                  << "\nis a pantry to the south, with the Mess to the west."
                  << std::endl;
    }


    bool inFront(Pack& pockets);
    bool left(Pack& pockets);
    bool right(Pack& pockets);
};

#endif // KITCHEN_H_INCLUDED
