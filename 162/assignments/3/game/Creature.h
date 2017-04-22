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

#ifndef CREATURE_H_INCLUDED
#define CREATURE_H_INCLUDED

class Creature
{
protected:
        int armor = 3,  //additional protection against attacks
            strength = 12; //health of the creature
        bool strong = true; //true if achilles is not cut
        bool goblin = false; //true if creature is a Goblin
        bool alive = true; //true if strength is greater than 0
        std::string name = ""; //name assigned to the creature

public:
        Creature(){};

        Creature(std::string name)
        { this -> name = name; }

        Creature(int arm, int str, std::string name)
        { armor = arm, strength = str, this ->name = name;}

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
