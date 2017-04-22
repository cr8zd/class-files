/*****************************************************************************************
** Program Filename: Shadow.h
** Author: Jennifer Frase
** Date: 2/15/15
** Description: a shadow creature who has a high attack and low defense, but may not
                receive damage 50% of the time
** Input: none
** Output: attack, defense, damage, and strength reports
*****************************************************************************************/
#include "Creature.h"

#include <string>

#ifndef SHADOW_H_INCLUDED
#define SHADOW_H_INCLUDED

class Shadow : public Creature
{
public:
    Shadow() : Creature(0, 12, "Shadow"){};

    Shadow(std::string name) : Creature(0, 12 ,name){};

    int attack()
    {
        int att = ((rand() % 10) + 1)
                + ((rand() % 10) + 1); //determines attack value

        if(!strong)
            att *= .5;

        std::cout << name << "'s attack: " << att << std::endl;
        return att;
    }

    void defense(int att, bool gob);
};

void Shadow::defense(int att, bool gob)
{
    int def = ((rand() % 6) + 1); //determines defense value
    int there = rand() % 2; //determines if damage is received

    if(gob && att == 12 && there != 0)//attacker cuts achilles if shadow is hit
        strong = false;

    int damage = (att - def) - armor; //calculates damage


    if (there == 0)
        damage = 0;

    std::cout << name << "'s defense: " << def << std::endl;
    std::cout << name << "'s damage: " << (damage > 0? damage: 0) << std::endl;

    if(damage >= 0)
        strength -= damage;

    std::cout << name << "'s strength: " << (strength > 0? strength: 0)
              << "/12" << std::endl;

    if(strength <= 0)
        alive = false;
}

#endif // SHADOW_H_INCLUDED
