/*****************************************************************************************
** Program Filename: Bedroom.cpp
** Author: Jennifer Frase
** Date: 3/17/15
** Description: implementation of bedroom.h that allows users to decide what to do
*****************************************************************************************/
#include <iostream>
#include <string>
#include <map>
#include "Room.h"
#include "Bedroom.h"
#include "Pack.h"
#include "response_check.h"

void Bedroom::describe(Pack& pockets)
{
    std::cout << "\nYou enter a bedroom, to the south is the hallway,"
              << "\nto the north is a bed, and to the east is a closet."
              << "\nA desk sits to the west of you."
              << std::endl;
}


/*****************************************************************************************
** Function: inFront
** Description: allow the user to find the journal under a bed
** Parameters: the inventory
** Pre-Conditions: none
** Post-Conditions: none
*****************************************************************************************/
bool Bedroom::inFront(Pack& pockets)
{
    if(underBed != "empty")
    {
        std::cout << "\nLooking under the bed you find a journal."
                  << "\nDo you want to snoop?"
                  << endl;
        char choice = responseCheck('Y', 'N');
        if(choice == 'Y')
        {
            std::cout << "Reading the journal you discover that the owner"
                      << " has a dog named Ralph,\nand that they both love"
                      << " ham and swiss sandwiches."
                      << std::endl;
        }
    }
    else
    {
        std::cout << "There was nothing under the bed." << std::endl;
    }
    return false;
}

/*****************************************************************************************
** Function: left
** Description: searches the deck if the user has the key
** Parameters: the inventory
** Pre-Conditions: inventory size must be 7
** Post-Conditions: none
*****************************************************************************************/
bool Bedroom::left(Pack& pockets)
{
    int pos = -1;
    for(int i = 0; i < 7; i++)
    {
        if(pockets[i].name == "key")
            pos = i;
    }

    if(inDesk != "empty")
    {
        if(pos >= 0)
        {
            pockets.removeItem(pockets[pos]);
            std::cout << "You use the key on the desk, and it opens."
                      << std::endl;
            std::cout << "\nLooking through the desk you find a bottle of sleeping pills."
                      << "\nDo you want to take them?"
                      << std::endl;
            char choice = responseCheck('Y', 'N');
            if(choice == 'Y')
            {
                Item newItem;
                newItem.size = 1;
                newItem.name = "medication";
                bool added = pockets.addItem(newItem);
                if(!added)
                    std::cout << "\nYou cannot carry that item, please remove an item"
                              << "\at a table."
                              << std::endl;
                else
                    inDesk = "empty";
            }
        }
        else
        {
            std::cout << "\nThe desk is locked, you do not have the key."
                      << std::endl;
        }
    }
    else
    {
        std::cout << "You find nothing useful in the desk." << std::endl;
    }
    return false;
}

/*****************************************************************************************
** Function: right
** Description: searches the closet
** Parameters: the inventory
** Pre-Conditions: none
** Post-Conditions: none
*****************************************************************************************/
bool Bedroom::right(Pack& pockets)
{
    /*if the key is not gone, then ask if the user want to pick it up, if so try to add*/
    if(inCloset != "empty")
    {
        std::cout << "\nLooking through the closet, you stumble upon a small key."
                  << "\nDo you want to take it?"
                  << endl;
        char choice = responseCheck('Y', 'N');
        if(choice == 'Y')
        {
            Item newItem;
            newItem.size = 1;
            newItem.name = "key";
            bool added = pockets.addItem(newItem);
            if(!added)
                std::cout << "\nYou cannot carry that item, please remove an item"
                          << "\at a table."
                          << std::endl;
            else
                inCloset = "empty";
        }
    }
    else
    {
        std::cout << "You find nothing useful in the closet."
                  << std::endl;
    }
    return false;
}

bool Bedroom::inBack(Pack& pockets)
{
    return true;
}
