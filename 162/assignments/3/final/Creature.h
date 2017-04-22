/*****************************************************************************************
** Program Filename: Creature.h
** Author: Jennifer Frase
** Date: 2/15/15
** Description: a base class of creatures
** Input: none
** Output: attack report
*****************************************************************************************/
#include <iostream>
#include <new>
#include <string>
#include <cstdlib>

#ifndef CREATURE_H_INCLUDED
#define CREATURE_H_INCLUDED

class Creature
{
protected:
        int armor,  //additional protection against attacks
            strength; //health of the creature
        bool strong; //true if achilles is not cut
        bool goblin; //true if creature is a Goblin
        bool alive; //true if strength is greater than 0
        std::string name; //name assigned to the creature

public:
        Creature()
        {
            armor = 3, strength = 12;
            strong = true, goblin = false, alive = true;
            name = "";
        }

        Creature(std::string name)
        {
            this -> name = name;
            armor = 3, strength = 12;
            strong = true, goblin = false, alive = true;
        }

        Creature(int arm, int str, std::string name)
        {
            armor = arm, strength = str;
            strong = true, goblin = false, alive = true;
            this ->name = name;
        }

        /*calculates and returns the attack value*/
        virtual int attack()
        {
            int att = ((rand() % 6) + 1) + ((rand() % 6) + 1);
            if(!(strong))
                att *= .5;

            std::cout << name << "'s attack: " << att << std::endl;
            return att;
        }

        /*calculates the damage received from an attack and applies
          it to the strength of the creature*/
        virtual void defense(int att, bool gob) = 0;

        bool isGoblin()
        { return goblin;} //returns true if creature is a Goblin

        bool getAlive()
        { return alive; } //returns true if strength > 0

        std::string getName()
        { return name; } //returns the name of the Creature
};


#endif // CREATURE_H_INCLUDED
