/*****************************************************************************************
** Program Filename: Kitchen.cpp
** Author: Jennifer Frase
** Date: 3/17/15
** Description: implementation of Kitchen.h
*****************************************************************************************/
#include <iostream>
#include <string>
#include <map>
#include <ctime>
#include "Room.h"
#include "Food.h"
#include "Kitchen.h"
#include "Pack.h"
#include "response_check.h"


/*****************************************************************************************
** Function: inFront
** Description: lists the possible ingredients that the user can pick from the fridge
** Parameters: the inventory
** Pre-Conditions: inventory must be size 7
** Post-Conditions: none
*****************************************************************************************/
bool Kitchen::inFront(Pack& pockets)
{
    Item newItem;
    std::cout << "\nWhat do you want from the fridges:"
              << "\n1) cheeses"
              << "\n2) meats"
              << "\n3) dressings"
              << "\n4) nothing"
              << std::endl;

    char choice = responseCheck('1', '2', '3', '4');

    /*look at the various cheeses*/
    if(choice == '1')
    {
        newItem.size = 3;
        std::cout << "\nWhat do you want from the cheeses:"
              << "\n1) chedder cheese"
              << "\n2) blue cheese"
              << "\n3) swiss cheese"
              << "\n4) american cheese"
              << "\n5) nothing"
              << std::endl;
        choice = responseCheck('1', '2', '3', '4', '5');
        if(choice == '1')
            newItem.name = "chedder cheese";
        else if(choice == '2')
            newItem.name = "blue cheese";
        else if(choice == '3')
            newItem.name = "swiss cheese";
        else if(choice == '4')
            newItem.name = "american cheese";
        else
            return false;
        bool added = pockets.addItem(newItem);
        if(!added)
            std::cout << "\nYou cannot carry that item, please remove an item"
                      << "\nby placing one on a table. Because the cheeses are in"
                      << "\nblocks, you need to empty a pocket or your hand."
                      << std::endl;
    }
    /*look at the various meats*/
    else if(choice == '2')
    {
        newItem.size = 4;
        std::cout << "\nWhat do you want from the meats:"
              << "\n1) roast beef"
              << "\n2) chicken"
              << "\n3) ham"
              << "\n4) bacon"
              << "\n5) nothing"
              << std::endl;
        choice = responseCheck('1', '2', '3', '4', '5');
        if(choice == '1')
            newItem.name = "roast beef";
        else if(choice == '2')
            newItem.name = "chicken";
        else if(choice == '3')
            newItem.name = "ham";
        else if(choice == '4')
            newItem.name = "bacon";
        else
            return false;
        bool added = pockets.addItem(newItem);
        if(!added)
            std::cout << "\nYou cannot carry that item, please remove an item"
                      << "\nby placing one on a table. Since the item wont fit"
                      << "\nin your pocket, you need to remove the "
                      << pockets[6].name << " that you are holding."
                      << std::endl;
    }
    /*look at the various dressing*/
    else if(choice == '3')
    {
        newItem.size = 4;
        std::cout << "\nWhat do you want from the dressings:"
              << "\n1) mayonnaise"
              << "\n2) ranch"
              << "\n3) butter"
              << "\n4) mustard"
              << "\n5) nothing"
              << std::endl;
        choice = responseCheck('1', '2', '3', '4', '5');
        if(choice == '1')
            newItem.name = "mayonnaise";
        else if(choice == '2')
            newItem.name = "ranch";
        else if(choice == '3')
            newItem.name = "butter";
        else if(choice == '4')
            newItem.name = "mustard";
        else
            return false;
        bool added = pockets.addItem(newItem);
        if(!added)
            std::cout << "\nYou cannot carry that item, please remove an item"
                      << "\nby placing one on a table. Since the item wont fit"
                      << "\nin your pocket, you need to remove the "
                      << pockets[6].name << " that you are holding."
                      << std::endl;
    }

    return false;
}

bool Kitchen::left(Pack& pockets)
{
    return true;
}


/*****************************************************************************************
** Function: right
** Description: looks at the various ingredients found in the pantry that the user can
**              take
** Parameters: the inventory
** Pre-Conditions: inventory must have a size greater than 7
** Post-Conditions: none
*****************************************************************************************/
bool Kitchen::right(Pack& pockets)
{
    Item newItem;
    std::cout << "\nWhat do you want from the pantry:"
              << "\n1) breads"
              << "\n2) vegetables"
              << "\n3) fruits"
              << "\n4) nothing"
              << std::endl;

    char choice = responseCheck('1', '2', '3', '4');

    /*looks at the various breads*/
    if(choice == '1')
    {
        newItem.size = 4;
        std::cout << "\nWhat do you want from the breads:"
              << "\n1) white"
              << "\n2) wheat"
              << "\n3) nothing"
              << std::endl;
        choice = responseCheck('1', '2', '3');
        if(choice == '1')
            newItem.name = "white bread";
        else if(choice == '2')
            newItem.name = "wheat bread";
        else
            return false;
        bool added = pockets.addItem(newItem);
        if(!added)
            std::cout << "\nYou cannot carry that item, please remove an item"
                      << "\nby placing one on a table. Since the item wont fit"
                      << "\nin your pocket, you need to remove the "
                      << pockets[6].name << " that you are holding."
                      << std::endl;
    }
    /*looks at the various vegetables*/
    else if(choice == '2')
    {
        newItem.size = 4;
        std::cout << "\nWhat do you want from the vegetables:"
              << "\n1) onion"
              << "\n2) lettuce"
              << "\n3) spinach"
              << "\n4) nothing"
              << std::endl;
        choice = responseCheck('1', '2', '3', '4');
        if(choice == '1')
            newItem.name = "onion";
        else if(choice == '2')
            newItem.name = "lettuce";
        else if(choice == '3')
            newItem.name = "spinach";
        else
            return false;
        bool added = pockets.addItem(newItem);
        if(!added)
            std::cout << "\nYou cannot carry that item, please remove an item"
                      << "\nby placing one on a table. Since the item wont fit"
                      << "\nin your pocket, you need to remove the "
                      << pockets[6].name << " that you are holding."
                      << std::endl;
    }
    /*look at the various fruits*/
    else if(choice == '3')
    {
        newItem.size = 3;
        std::cout << "\nWhat do you want from the fruits:"
              << "\n1) apple"
              << "\n2) tomato"
              << "\n3) cucumber"
              << "\n4) nothing"
              << std::endl;
        choice = responseCheck('1', '2', '3', '4');
        if(choice == '1')
            newItem.name = "apple";
        else if(choice == '2')
            newItem.name = "tomato";
        else if(choice == '3')
            newItem.name = "cucumber";
        else
            return false;
        bool added = pockets.addItem(newItem);
        if(!added)
            std::cout << "\nYou cannot carry that item, please remove an item"
                      << "\nby placing one on a table. Since the item is medium in"
                      << "\nsize, you need to clear out a pocket or your hand."
                      << std::endl;
    }
    return false;
}
