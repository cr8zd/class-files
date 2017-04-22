/*****************************************************************************************
** Program Filename: Goblin.h
** Author: Jennifer Frase
** Date: 2/15/15
** Description: a goblin creature with low everything, but able to
                hinder opponents if attack is the max
** Input: none
** Output: defense, damage, and strength reports
*****************************************************************************************/
#include "Creature.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>


#ifndef GOBLIN_H_INCLUDED
#define GOBLIN_H_INCLUDED

class Goblin: public Creature
{
public:
    Goblin(): Creature(3, 8, "Goblin")
    { goblin = true; }

    Goblin(std::string name): Creature(3, 8, name)
    { goblin = true; }

    void defense(int att, bool gob);
};

void Goblin::defense(int att, bool gob)
{
    int def = (rand() % 6) + 1;  //determines defense value
    int damage = (att - def) - armor;  //calculates damage

    std::cout << name << "'s defense: " << def << std::endl;
    std::cout << name << "'s damage: " << (damage > 0? damage: 0) << std::endl;

    if(damage >= 0)
        strength -= damage;

    std::cout << name
              << "'s strength: "
              << (strength > 0? strength: 0)
              << "/8" << std::endl;

    if(strength <= 0)
        alive = false;
}

#endif // GOBLIN_H_INCLUDED
