/*****************************************************************************************
** Program Filename: Food.cpp
** Author: Jennifer Frase
** Date: 3/17/15
** Description: implementation of Food.h
*****************************************************************************************/
#include <iostream>
#include <string>
#include <map>
#include "Room.h"
#include "Food.h"
#include "response_check.h"


void Food::describe(Pack& pockets)
{
    std::cout << "\nYou have enter the mess hall. To the north is"
              << "\nthe hall and the east is the kitchens. There are"
              << "\ntables to the south, and stacks of dinnerware are"
              << "\nto the west, covering most of that table."
              << std::endl;
}

bool Food::inFront(Pack& pockets)
{
    return true;
}


/*****************************************************************************************
** Function: left
** Description: creates a new item if the user wants to pick one up, and attempts to add
**              it to the inventory
** Parameters: the inventory
** Pre-Conditions: inventory must be size 7
** Post-Conditions: none
*****************************************************************************************/
bool Food::left(Pack& pockets)
{
    Item newItem;
    newItem.size = 4;
    std::cout << "\nWhat do you want to take from the dinnerware:"
              << "\n1) plate"
              << "\n2) knife"
              << "\n3) bowl"
              << "\n4) nothing"
              << std::endl;

    char choice = responseCheck('1', '2', '3', '4');
    if(choice == '1')
        newItem.name = "plate";
    else if(choice == '2')
        newItem.name = "knife";
    else if(choice == '3')
        newItem.name = "bowl";
    else
        return false;
    bool added = pockets.addItem(newItem);
    if(!added)
        std::cout << "\nYou cannot carry that item, please remove an item"
                      << "\nby placing one on a table. Since the item wont fit"
                      << "\nin your pocket, you need to remove the "
                      << pockets[6].name << " that you are holding."
                      << std::endl;
    return false;
}

bool Food::right(Pack& pockets)
{
    return true;
}


/*****************************************************************************************
** Function: inBack
** Description: allows for messing with the table, such as adding/removing items and
                making a sandwich
** Parameters: the inventory
** Pre-Conditions: inventory must be size 7
** Post-Conditions: none
*****************************************************************************************/
bool Food::inBack(Pack& pockets)
{
    std::cout << "\nWhat do you want to do at the table:"
              << "\n1) put item on table"
              << "\n2) pick up item from table"
              << "\n3) make sandwich"
              << "\n4) nothing"
              << std::endl;

    char choice = responseCheck('1', '2', '3', '4');

    /*put an item from the inventory onto the table before removing from inventory*/
    if(choice == '1')
    {
        std::cout << "What item from your pockets and hand do you want to place"
                  << std::endl;

        /*list items in inventory*/
        for(int i = 0; i < 7; i++)
        {
            if(i == 0)
            {
                std::cout << "\nRight Pocket:"
                          << "\n" << pockets[i].name;
            }
            else if (i == 3)
            {
                std::cout << "\n\nLeft Pocket"
                          << "\n" << pockets[i].name;
            }
            else if(i == 6)
            {
                std::cout << "\n\nHands"
                          << "\n" << pockets[i].name;
            }
            else if(pockets[i].name != "empty")
            {
                std::cout << "\n" << pockets[i].name;
            }
        }

        std::string itemName;
        std::cout << std::endl;
        getline(cin, itemName);

        /*searches for the position of the item, and moves it*/
        int pos = -1;
        for(int i = 0; i < 7; i++)
        {
            if(pockets[i].name == itemName)
                pos = i;
        }
        if(pos >= 0)
        {
            for(int i = 0; i < 15; i++)
            {
                if(table[i].name == "empty")
                {
                    table[i] = pockets[pos];
                    break;
                }
            }
            pockets.removeItem(pockets[pos]);
        }
    }
    /*move an item into the inventory before removing it from table*/
    else if(choice == '2')
    {
        std::cout << "What item do you want to take from the table?"
                  << std::endl;

        /*lists the tables contents*/
        for(int i = 0; i < 15; i++)
        {

            if(i == 0)
            {
                std::cout << "Table:"
                          << "\n" << table[i].name;
            }
            else if(table[i].name != "empty")
                std::cout << "\n" << table[i].name;
        }

        std::cout << std::endl;
        std::string itemName;
        getline(cin, itemName);

        /*finds the position of the item and moves it*/
        int pos = -1;
        for(int i = 0; i < 15; i++)
        {
            if(table[i].name == itemName)
                pos = i;
        }
        if(pos >= 0)
        {
            bool added = pockets.addItem(table[pos]);
            if(!added)
            {
                std::cout << "\nYou cannot carry that item, please remove an item"
                          << "\nby placing one on a table. Since the item wont fit"
                          << "\nin your pocket, you need to remove the "
                          << pockets[6].name << " that you are holding."
                          << std::endl;
                return false;
            }
            Item removal("empty", 0);
            table[pos] = removal;
        }
    }
    /*creates a sandwich*/
    else if(choice == '3')
    {
        std::string ing1,
                    ing2,
                    ing3;
        std::cout << "\nTo make a sandwich, you need bread and three"
                  << "\nother ingredients. You also need a knife and plate. All"
                  << "\nneed to be on the table."
                  << std::endl;

        /*lists table*/
        for(int i = 0; i < 15; i++)
        {
             if(i == 0)
            {
                std::cout << "Table:"
                          << "\n" << table[i].name;
            }
            else if(table[i].name != "empty")
            {
                std::cout << "\n" << table[i].name;
            }
        }

        std::cout << "\n\nWhat three ingredients, do you want to add to the sandwich?"
                  << std::endl;
        std::cout << "\nFirst ingredient: ";
        getline(cin, ing1);
        std::cout << "\nSecond ingredient: ";
        getline(cin, ing2);
        std::cout << "\nThird ingredient: ";
        getline(cin, ing3);
        std::cout << std::endl;
        Pack sandwich;

        /*find the positions of all the items*/
        int posK = -1,
            posP = -1,
            pos = -1,
            posW = -1,
            pos1 = -1,
            pos2 = -1,
            pos3 = -1;

        for(int i = 0; i < 15; i++)
        {
            if(table[i].name == "knife")
                posK = i;
            else if(table[i].name == "plate")
                posP = i;
            else if(table[i].name == "white bread")
                pos = i;
            else if(table[i].name == "wheat bread")
                posW = i;
            else if(table[i].name == ing1)
                pos1 = i;
            else if(table[i].name == ing2)
                pos2 = i;
            else if(table[i].name == ing3)
                pos3 = i;
        }

        /*add the knife to the sandwich if it is there*/
        if(posK < 0)
        {
            std::cout << "\nYou do not have a knife at the table."
                      << std::endl;
            return false;
        }
        else
        {
            sandwich[0] = table[posK];
        }

        /*add the plate to the sandwich if it is there*/
        if(posP < 0)
        {
            std::cout << "\nYou do not have a plate at the table."
                      << std::endl;
            return false;
        }
        else
        {
            sandwich[1] = table[posP];
        }

        /*add a bread to the sandwich if one is there, if two, then ask*/
        if(pos >= 0 && posW >= 0)
        {
            std::cout << "Which bread do you want to use?"
                      << "\n1) white"
                      << "\n2) wheat"
                      << std::endl;
            choice = responseCheck('1', '2');
            if(choice == '1')
                sandwich[2] = table[pos];
            else if(choice == '2')
                sandwich[2] = table[posW];
            else
                std::cout << "error Food make sandwich bread";
        }
        else if (pos >= 0)
        {
            sandwich[2] = table[pos];
        }
        else if (posW >= 0)
        {
            sandwich[2] = table[posW];
        }
        else
        {
            std::cout << "\nThere is no bread on the table."
                      << std::endl;
            return false;
        }

        /*add the first to the sandwich if it is there*/
        if(pos1 < 0)
        {
            std::cout << "\nYou do not have a " << ing1 << " at the table."
                      << std::endl;
            return false;
        }
        else
        {
            sandwich[3] = table[pos1];
        }

        /*add the second to the sandwich if it is there*/
        if(pos2 < 0)
        {
            std::cout << "\nYou do not have a " << ing2 << " (your 2nd ingredient) at the table."
                      << std::endl;
            return false;
        }
        else
        {
            sandwich[4] = table[pos2];
        }

        /*add the third ingredient to the sandwich if it is there*/
        if(pos3 < 0)
        {
            std::cout << "\nYou do not have a " << ing3 << " (your 3rd ingredient) at the table."
                      << std::endl;
            return false;
        }
        else
        {
            sandwich[5] = table[pos3];
        }

        /*make the sandwich and add to the pockets*/
        Item newItem;
        newItem.size = 4;

        /*names the created sandwich based on how accurate the ingredients were*/
        if((ing1 == "medication" || ing2 == "medication" || ing3 == "medication")
           && (ing1 == "swiss cheese" || ing2 == "swiss cheese" || ing3 == "swiss cheese")
           && (ing1 == "ham" || ing2 == "ham" || ing3 == "ham"))
        {
            newItem.name = "medicated ham and swiss";
        }
        else if((ing1 == "medication" || ing2 == "medication" || ing3 == "medication"))
        {
            newItem.name = "medicated sandwich";
        }
        else if((ing1 == "swiss cheese" || ing2 == "swiss cheese" || ing3 == "swiss cheese")
                && (ing1 == "ham" || ing2 == "ham" || ing3 == "ham"))
        {
            newItem.name = "ham and swiss";
        }
        else
            newItem.name = "sandwich";

        bool added = pockets.addItem(newItem);
        if(!added)
        {
            std::cout << "\nYou cannot carry that item, please remove an item"
                      << "\nby placing one on a table. Since the item wont fit"
                      << "\nin your pocket, you need to remove the "
                      << pockets[6].name << " that you are holding."
                      << std::endl;
            table.addItem(newItem);
        }

        std::cout << "\nA " << newItem.name << " has been made." << std::endl;
    }
    return false;
}
