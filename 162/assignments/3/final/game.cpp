/*****************************************************************************************
** Program Filename: game.cpp
** Author: Jennifer Frase
** Date: 2/15/15
** Description: pits two user picked creatures against each other in a fight
** Input: numbers representing which creatures are picked
** Output: results from each round of the fights
*****************************************************************************************/
#include <iostream>
#include <new>
#include <cstdlib>
#include <ctime>
#include <string>

#include "Creature.h"
#include "Goblin.h"
#include "Barbarian.h"
#include "Blue.h"
#include "Reptile.h"
#include "Shadow.h"
#include "response_check.h"

/*****************************************************************************************
** Function: fight
** Description: continues to make two creatures fight, switching who is attacking vs
                defending each round, until one of the creatures no longer can
** Parameters:  two Creature pointers
** Pre-Conditions: pointers can't be null
** Post-Conditions: none
*****************************************************************************************/
void fight(Creature *attacker, Creature *defender)
{
    Creature *temp;
    while(attacker -> getAlive() && defender -> getAlive())
    {
        std::cout << attacker -> getName()
                  << " attacks "
                  << defender -> getName()
                  << std::endl;
        int att = attacker -> attack();
        defender -> defense(att, attacker -> isGoblin());
        temp = attacker;
        attacker = defender;
        defender = temp;
        std::cin.get();
    }

    std::cout << attacker -> getName() << " was defeated by "
              << defender -> getName() << std::endl;
}

/*****************************************************************************************
** Function: pick
** Description: gives a list of creatures to pick from and returns that choice
** Parameters:  a string, signifies what round of picking the creature is ie second, third
                should have a space at the end of the name
** Pre-Conditions: none
** Post-Conditions: none
*****************************************************************************************/
char pick(std::string number)
{
    std::cout << "What " << number << "creature do you want to fight?"
              << "\n1) Goblin"
              << "\n2) Barbarian"
              << "\n3) Reptile"
              << "\n4) Blue Men"
              << "\n5) Shadow"
              << std::endl;
    return responseCheck('1', '2', '3', '4', '5');
}

int main()
{
    srand(time(NULL));
    Creature *attacker;
    Creature *defender;

    /*play out a fight until the user doesn't want to play another*/
    do
    {
        /*pick the first creature and assign it to attacker*/
        char choice = pick("");
        if(choice == '1')
            attacker = new Goblin("Goblin 1");
        else if(choice == '2')
            attacker = new Barbarian("Barbarian 1");
        else if(choice == '3')
            attacker = new Reptile("Reptilian 1");
        else if(choice == '4')
            attacker = new Blue("Blue Men 1");
        else if(choice == '5')
            attacker = new Shadow("Shadow 1");
        else
            return 1;

        /*pick a second creature and assign it to defender*/
        choice = pick("second ");
        if(choice == '1')
            defender = new Goblin("Goblin 2");
        else if(choice == '2')
            defender = new Barbarian("Barbarian 2");
        else if(choice == '3')
            defender = new Reptile("Reptilian 2");
        else if(choice == '4')
            defender = new Blue("Blue Men 2");
        else if(choice == '5')
            defender = new Shadow("Shadow 2");
        else
            return 2;

        fight(attacker, defender);

        delete attacker;
        delete defender;

        std::cout << "\nDo you want to play another round?" << std::endl;
    }while(responseCheck('Y', 'N', '\0', '\0', '\0') == 'Y');

    return 0;
}
