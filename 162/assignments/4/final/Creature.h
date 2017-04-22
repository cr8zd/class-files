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
            strength, //health of the creature
            maxStrength, //max health of the creature
            points, //points earned during battle
            team, //team number
            rating; //likelihood the creature will win out of a hundred
        bool strong; //true if achilles is not cut
        bool goblin; //true if creature is a Goblin
        bool alive; //true if strength is greater than 0
        std::string name; //name assigned to the creature

public:
        Creature()
        {
            armor = 3, strength = 12, rating = 90;
            maxStrength = 12, points = 0, team = 1;
            strong = true, goblin = false, alive = true;
            name = "";
        }

        Creature(int tm, std::string name)
        {
            this -> name = name;
            armor = 3, strength = 12, rating = 90;
            maxStrength = 12, points = 0, team = tm;
            strong = true, goblin = false, alive = true;
        }

        Creature(int rate, int arm, int str, int tm, std::string name)
        {
            armor = arm, strength = str, rating = rate;
            maxStrength = str, points = 0, team= tm;
            strong = true, goblin = false, alive = true;
            this ->name = name;
        }

        /*calculates and returns the attack value*/
        virtual int attack()
        {
            int att = ((rand() % 6) + 1) + ((rand() % 6) + 1);
            if(!(strong))
                att *= .5;

//            std::cout << name << "'s attack: " << att << std::endl;
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

        int getRating()
        { return rating; } //returns the likehood the creature will win

        int getStr()
        { return strength; } //returns current health of creature

        int getMaxStr()
        { return maxStrength; } //returns max health of creature

        void addPoints(int poi)
        { points += poi; } //adds points to creature

        void addStrength(int str)
        {
            strength += str;
            if(strength > maxStrength)
                strength = maxStrength;
        }

        int getPoints()
        { return points; }

        int getTeam()
        { return team; }
};


#endif // CREATURE_H_INCLUDED
