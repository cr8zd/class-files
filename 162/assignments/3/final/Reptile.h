/*****************************************************************************************
** Program Filename: Reptile.h
** Author: Jennifer Frase
** Date: 2/15/15
** Description: a reptilian who has a higher than average attack, armor, and strength,
                but a low defense
** Input: none
** Output: attack, defense, damage, and strength reports
*****************************************************************************************/
#include "Creature.h"

#include <iostream>
#include <string>
#include <cstdlib>

#ifndef REPTILE_H_INCLUDED
#define REPTILE_H_INCLUDED

class Reptile:public Creature
{
public:
    Reptile (): Creature (7, 18, "Reptilian"){};

    Reptile (std::string name): Creature (7, 18, name){};

    int attack()
    {
        int att = ((rand() % 6) + 1)
                + ((rand() % 6) + 1)
                + ((rand() % 6) + 1);  //determines defense value

        if(!strong)
            att *= .5;

        std::cout << name << "'s attack: " << att << std::endl;
        return att;
    }

    void defense(int att, bool gob);
};

void Reptile::defense(int att, bool gob)
{
    int def = (rand() % 6) + 1; //determines defense value

    if(gob && att == 12)
        strong = false;

    int damage = (att - def) - armor; //calculates damage

    std::cout << name << "'s defense: " << def << std::endl;
    std::cout << name << "'s damage: " << (damage > 0? damage: 0) << std::endl;

    if(damage >= 0)
        strength -= damage;

    std::cout << name << "'s strength: " << (strength > 0? strength: 0)
          << "/18" << std::endl;

    if(strength <= 0)
        alive = false;
}

#endif // REPTILE_H_INCLUDED
