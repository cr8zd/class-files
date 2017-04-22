/*****************************************************************************************
** Program Filename: main.cpp
** Author: Jennifer Frase
** Date: 3/17/15
** Description: runs a text based escape game
** Input: numbers and letter which represent choices the user can make
** Output: text on the game, where the user is, what they can do...
*****************************************************************************************/
#include <iostream>
#include <new>
#include <ctime>
#include "Guarded.h"
#include "Bedroom.h"
#include "Food.h"
#include "Hall.h"
#include "Portal.h"
#include "Kitchen.h"
#include "Pack.h"
#include "Elevator.h"
#include "response_check.h"

/*****************************************************************************************
** Function: makeStruct
** Description: links the various rooms together
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: a room pointer is returned
*****************************************************************************************/
Room* makeStruct()
{
    Room *current = new Kitchen();
    Room *last = current;
    current = new Food("Mess Hall");
    last->setWest(current); //connect kitchen to mess hall
    current->setEast(last); //connect mess hall to kitchen
    last = current;
    current = new Hall("Floor 1 Hall");
    last->setNorth(current); //connect mess hall to hall 1
    current->setSouth(last); //connect hall 1 to mess hall
    last = current;
    current = new Guarded("Office");
    last->setEast(current);  //connect hall 1 to the office
    current = new Elevator();
    last->setWest(current); //connect hall 1 to the elevator
    current->setSouth(last); //connect elevator to hall 1
    last = current;
    current = new Hall("Floor 2 Hall");
    last->setEast(current); //connect elevator to hall 2
    current->setWest(last); //connect hall 2 to elevator
    last = current;
    current = new Portal();
    current->setEast("Home, Sweet Home");
    current->setWest(last); //connect Portal room to hall 2
    last->setEast(current); //connect hall 2 to portal room
    last->setNorth("Locked Door");
    last->setSouth("Locked Door");
    current = new Hall("Floor 3 Hall");
    last = last->goWest();
    last->setNorth(current); //connect elevator to hall 3
    current->setWest(last); //connect hall 3 to elevator
    last = current;
    current = new Bedroom("3A", "empty", "medication", "key");
    last->setSouth(current); //connect hall 3 to bedroom 3A
    current->setSouth(last); //connect bedroom 3A to hall 3
    current = new Guarded("3C Bunks");
    last->setEast(current); //connect hall 3 to 3C
    current = new Bedroom("3B", "journal", "empty", "empty");
    last->setNorth(current); //connect hall 3 to 3B
    current->setSouth(last); //connect 3B to hall 3
    return current; //return 3B
}

/*****************************************************************************************
** Function: deleteRooms
** Description: deletes all the rooms made in makeStruct
** Parameters: a pointer to the first room
** Pre-Conditions: the pointer must be to room 3B
** Post-Conditions: none
*****************************************************************************************/
void deleteRooms(Room *current)
{
    /*current starts at 3B*/
    Room *next = current->goSouth(); //hall 3
    delete current; //delete 3B
    current = next;
    next = current->goEast();//3C
    delete next;//delete 3C
    next = current->goSouth(); //3A
    delete next; //delete 3A
    next = current->goWest(); //elevator
    delete current; //delete hall 3
    current = next->goEast();//hall 2
    next = current->goEast(); //portal
    delete next; //delete portal
    next = current->goWest(); //elevator
    delete current; //delete hall 2
    current = next->goSouth(); //hall 1
    delete next; //delete elevator
    next = current->goEast(); // office
    delete next; //delete office
    next = current->goSouth(); // mess hall
    delete current; // delete hall 1
    current = next->goEast(); //kitchen
    delete next; //delete mess hall
    delete current; //delete kitchen
}

int main()
{

    const int SCREEN_PUSH = 25;
    const int maxSteps = 20;
    int currentSteps = 0;
    Room *current = makeStruct();
    Room *last = current;
    Pack jacket;
    std::string direction;
    std::string space;
    bool exit = false;
    bool hall1 = false;
    bool hall2 = false;
    bool hall3 = false;

    space.assign(SCREEN_PUSH, '\n');

    std::cout << "You are an alien, and you accidentally walked through a door onto"
              << "\nEarth. Luckily, you have not been here long, and the dastardly "
              << "\nhumans seem easily tired. As such, when your guard fell asleep"
              << "\nyou squirmed through those incompetent bars and took over his"
              << "\nbody. With him asleep, you have very little time before he"
              << "\nnaturally wakes up and regains control. In addition, you will"
              << "\nbe immediately noticed if anyone looks too closely at you,"
              << "\nbecause... well... your tail hangs out of this man's cramped"
              << "\nhead. How these beings can stand such...such solid bodies"
              << "\nyou will never know."
              << std::endl;

    std::cout << "\nLooking down at the body you are inhabiting, you see that you are"
              << "\nfairly well built and you fill out your uniform... which means"
              << "\nyou can't hide things very well. Still though, the uniform"
              << "\ndoes come with two medium sized pockets where each could hold a"
              << "\nsmall book. I guess you will just have to do with carrying some"
              << "\nthings. Though, since you are not used to this body, you figure"
              << "\nyou can only carry in your hands one thing at a time."
              << std::endl;
    std::cin.get();
    std::cout << space;

    current->describe(jacket);
    /*play until caught or escaped*/
    do
    {
        if(current->isCaught() || currentSteps > maxSteps)
            break;

        /*print what the user can see/do and get their choice*/
        std::cout << "\nYou are currently in the room " << current->getName() << ", "
                  << "where you can go to"
                  << "\nN) " << current->getNName()
                  << "\nS) " << current->getSName()
                  << "\nW) " << current->getWName()
                  << "\nE) " << current->getEName()
                  << "\nG) Goal"
                  << "\nWhich direction do you want to go?" << std::endl;
        char choice = responseCheck('N', 'S', 'W', 'E', 'G');


        bool advance;
        /*call the appropriate functions and if the direction is a door, advance to the
          next room*/
        if(choice == 'N')
        {
            std::cout << space;
            advance = current->inFront(jacket);
            if(advance && current->getNName() != "Locked Door"
               && current->getNName() != "wall")
            {
                current = current->goNorth();
                current->describe(jacket);
                currentSteps++;
            }
        }
        else if(choice == 'S')
        {
            std::cout << space;
            advance = current->inBack(jacket);
            if(advance && current->getSName() != "Locked Door"
               && current->getSName() != "wall")
            {
                current = current->goSouth();
                current->describe(jacket);
                currentSteps++;
            }
        }
        else if(choice == 'W')
        {
            std::cout << space;
            advance = current->left(jacket);
            if(advance)
            {
                current = current->goWest();
                current->describe(jacket);
                currentSteps++;
            }
        }
        else if(choice == 'E')
        {
            std::cout << space;
            advance = current->right(jacket);
            if(current->getName() == "Floor 1 Hall" && !hall1)
            {
                current->goEast()->peek();
                hall1 = true;
            }
            else if(current->getName() == "Floor 2 Hall" && !hall2)
            {
                current->goEast()->peek();
                hall2 = true;
            }
            else if(current->getName() == "Floor 3 Hall" && !hall3)
            {
                current->goEast()->peek();
                hall3 = true;
            }
            else if(advance && current->getName() == "Portal")
            {
                exit = true;
            }
            else if (advance)
            {
                current = current->goEast();
                current->describe(jacket);
                currentSteps++;
            }
        }
        else if(choice == 'G')
        {
            std::cout << space << "\nThe goal of the game is to make a drugged ham and swiss sandwich,"
                      << "\nand escape through the portal in under 20 room changes."
                      << std::endl;
        }
        else
            std::cout << space << "\nSomething went wrong" << std::endl;

    }while(!exit);

    /*print the appropriate message depending on if they escaped or were caught*/
    if(exit)
        std::cout << space << "\nYou have managed to escape back to home. Where you immediate;y lock"
                  << "\nthe door, praying no one unsuspecting might ever step through"
                  << "\nagain, lest they be tortured into giving up all their squid."
                  << std::endl;
    else
        std::cout << "\nYou were immediately caught, and they now know about your ability."
                  << "\nYour life is over; you may as well just give into their"
                  << "\ndemands of free squid."
                  << std::endl;
    deleteRooms(last);
    return 0;
}
