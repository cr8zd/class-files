/*****************************************************************************************
** Program Filename: Barbarian.h
** Author: Jennifer Frase
** Date: 2/15/15
** Description: a barbarian who has a low attack, average defense, no armor and average
                health
** Input: none
** Output: defense, damage, and strength reports
*****************************************************************************************/
#include "Creature.h"

#include <iostream>
#include <string>

#ifndef BARBARIAN_H_INCLUDED
#define BARBARIAN_H_INCLUDED

class Barbarian: public Creature
{
public:
    Barbarian(): Creature(0, 12, "Barbarian"){};

    Barbarian(std::string name): Creature(0, 12, name){};

    void defense(int att, bool gob);
};

void Barbarian::defense(int att, bool gob)
{
    int def = ((rand() % 6) + 1) + ((rand() % 6) + 1); //determines defense value

    if(gob && att == 12)
        strong = false;

    int damage = (att - def) - armor;  //calculates damage

    std::cout << name << "'s defense: " << def << std::endl;
    std::cout << name << "'s damage: " << (damage > 0? damage: 0)
              << std::endl;

    if(damage >= 0)
        strength -= damage;

    std::cout << name << "'s strength: " << (strength > 0? strength: 0)
              << "/12"  << std::endl;

    if(strength <= 0)
        alive = false;
}

#endif // BARBARIAN_H_INCLUDED
