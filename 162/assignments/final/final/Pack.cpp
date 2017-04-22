/*****************************************************************************************
** Program Filename: Pack.cpp
** Author: Jennifer Frase
** Date: 3/17/15
** Description: implementation of Pack.h's add and remove functions
*****************************************************************************************/
#include <iostream>
#include <string>
#include "Pack.h"


/*****************************************************************************************
** Function: addItem
** Description: adds an item to the Pack, if the pack is size 7, then there are 3 areas
**              for things to be stored, and they cannot mix.
** Parameters: an item that represents the item being added
** Pre-Conditions: none
** Post-Conditions: none
*****************************************************************************************/
bool Pack::addItem(Item newItem)
{
    /*if size is 7, treat the array like 3 separate entities*/
    if(sizeLimit == 7)
    {
        /*if the item could fit in the first pocket, return true*/
        if(pack[0].size + pack[1].size + pack[2].size
           + newItem.size <= 3)
        {
            if(pack[0].name == "empty")
                pack[0] = newItem;
            else if(pack[1].name == "empty")
                pack[1] = newItem;
            else if(pack[2].name == "empty")
                pack[2] = newItem;
            return true;
        }
        /*if the item could fit in the second pocket, return true*/
        else if(pack[3].size + pack[4].size + pack[5].size
           + newItem.size <= 3)
        {
            if(pack[3].name == "empty")
                pack[3] = newItem;
            else if(pack[4].name == "empty")
                pack[4] = newItem;
            else if(pack[5].name == "empty")
                pack[5] = newItem;
            return true;
        }
        /*if the item can be held, return true*/
        else if(pack[6].name == "empty")
        {
            pack[6] = newItem;
            return true;
        }
    }
    /*add the item anywhere that is free*/
    else
    {
        for(int i = 0; i < 15; i++)
        {
            if(pack[i].name == "empty")
            {
                pack[i] = newItem;
                return true;
            }
        }
    }
    return false;
}

/*****************************************************************************************
** Function: removeItem
** Description: removes the passed in Item from the Pack
** Parameters: the item being removed
** Pre-Conditions: none
** Post-Conditions: none
*****************************************************************************************/
void Pack::removeItem(Item old)
{
    for(int i = 0; i < sizeLimit; i++)
    {
        if(pack[i].name == old.name)
        {
            pack[i].name = "empty";
            pack[i].size = 0;
        }
    }
}
