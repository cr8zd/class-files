/*****************************************************************************************
** Program Filename: Blue.h
** Author: Jennifer Frase
** Date: 2/15/15
** Description: a blue men who fight in groups resulting in high attack and defense, but
                with low armor and average strength
** Input: none
** Output: attack, defense, damage, and strength reports
*****************************************************************************************/
#include "Creature.h"

#include <iostream>
#include <string>
#include <cstdlib>

#ifndef BLUE_H_INCLUDED
#define BLUE_H_INCLUDED

class Blue : public Creature
{
public:
    Blue() : Creature(1, "Blue Men"){};

    Blue(int tm, std::string name) : Creature(tm, name){};

    int attack()
    {
        int att = ((rand() % 10) + 1)
                + ((rand() % 10) + 1); //determines attack value

        if(!strong)
            att *= .5;

//        std::cout << name << "'s attack: " << att << std::endl;

        return att;
    }

    void defense(int att, bool gob);
};

void Blue::defense(int att, bool gob)
{
    int def = ((rand() % 6) + 1)
            + ((rand() % 6) + 1)
            + ((rand() % 6) + 1); //determines defense value

    if(gob && att == 12)
        strong = false;

    int damage = (att - def) - armor; //calculates damage

//    std::cout << name << "'s defense: " << def << std::endl;
//    std::cout << name << "'s damage: " << (damage > 0? damage: 0)
//              << std::endl;

    if(damage >= 0)
        strength -= damage;

//    std::cout << name << "'s strength: " << (strength > 0? strength: 0)
//              << "/12" << std::endl;

    if(strength < 0)
        strength = 0;

    if(strength == 0)
        alive = false;
}

#endif // BLUE_H_INCLUDED
