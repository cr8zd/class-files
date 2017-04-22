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
#include <queue>
#include <map>

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
Creature* fight(Creature *attacker, Creature *defender, std::map<int, Creature*> &losers)
{
    Creature *temp;
    while(attacker -> getAlive() && defender -> getAlive())
    {
//        std::cout << attacker -> getName()
//                  << " attacks "
//                  << defender -> getName()
//                  << std::endl;
        int att = attacker -> attack();
        defender -> defense(att, attacker -> isGoblin());
        temp = attacker;
        attacker = defender;
        defender = temp;
    //    std::cin.get();
    }
    int loserPnts = attacker->getPoints();

    while(losers.find(loserPnts) != losers.end())
    {
        loserPnts++;
    }

    losers[loserPnts] = attacker;
    int winnerPnts = ((attacker->getRating()*10) / defender->getRating());
                         //+ (defender->getMaxStr() - defender->getStr());
    defender->addPoints(winnerPnts);

    std::cout << attacker -> getName() << " was defeated wtih " << loserPnts
              << " points by\n" << defender -> getName() << " who won "
              << winnerPnts << " points for a total of " << defender->getPoints()
              << " points.\n" << std::endl;
    return defender;
}

/*****************************************************************************************
** Function: pick
** Description: gives a list of creatures to pick from and returns that choice
** Parameters:  a string, signifies what round of picking the creature is ie second, third
                should have a space at the end of the name
** Pre-Conditions: none
** Post-Conditions: none
*****************************************************************************************/
char pick(int number)
{
    std::cout << "What creature do you want to fight in round " << number << "?"
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
    const int TEAMS_NUM = 2;
    srand(time(NULL));
    Creature *attacker;
    Creature *winner;
    std::queue<Creature*> first, second, winning;
    std::map<int, Creature*> losers;
    int fighters;

    /*play out a fight until the user doesn't want to play another*/
    do
    {
        do
        {
            if(cin.fail())
            {
                std::cout << "That is an invalid input." << std::endl;
                std::cin.ignore(100000, '\n');
                std::cin.clear();
            }
            std::cout << "How many fighters on each team do you want?"
                      << std::endl;
            std::cin >> fighters;
            std::cin.get();
        }while(std::cin.fail());

        for(int i = 1; i <= 2; i++)
        {
            std::cout << "\nTeam " << i << " please pick your creatures."
                      << std::endl;

            /*pick the creatures*/
            for(int j = 1; j <= fighters; j++)
            {
                std::string name;
                char choice = pick(j);

                std::cout << "What name do you want to give the creature?"
                          << std::endl;
                std::getline(cin, name);
                std::cout << std::endl;

                if(choice == '1')
                    attacker = new Goblin(i, name);
                else if(choice == '2')
                    attacker = new Barbarian(i, name);
                else if(choice == '3')
                    attacker = new Reptile(i, name);
                else if(choice == '4')
                    attacker = new Blue(i, name);
                else if(choice == '5')
                    attacker = new Shadow(i, name);
                else
                    return 1;

                if(i == 1)
                    first.push(attacker);
                else if (i == 2)
                    second.push(attacker);
            }
        }

        int round = 1;
        while(!first.empty() && !second.empty())
        {
            if(round % TEAMS_NUM == 1)
                winner = fight(first.front(), second.front(), losers);
            else if(round % TEAMS_NUM == 0)
                winner = fight(second.front(), first.front(), losers);

            first.pop();
            second.pop();

            if(winner->getTeam() == 1)
            {
                winner->addStrength(first.size() / 2);
                first.push(winner);
            }
            else if(winner->getTeam() == 2)
            {
                winner->addStrength(second.size() / 2);
                second.push(winner);
            }
        }

        if(!first.empty())
        {
            while(!first.empty())
            {
                winner = first.front();
                int pnts = winner->getPoints();

                while(losers.find(pnts) != losers.end())
                {
                    pnts++;
                }

                losers[pnts] = winner;
                first.pop();
            }
        }
        else if (!second.empty())
        {
            while(!second.empty())
            {
                winner = second.front();
                int pnts = winner->getPoints();

                while(losers.find(pnts) != losers.end())
                {
                    pnts++;
                }

                losers[pnts] = winner;
                second.pop();
            }
        }

        std::cout << "\nThe top 3 scoring creatures were:" << std::endl;

        int count = 0,
            team1 = 0,
            team2 = 0;
        for(auto i = losers.rbegin(); i != losers.rend(); ++i)
        {
            if(count < 3)
                std::cout << i->second->getName() << ": "
                          << i->first << "pts for team "
                          << i->second->getTeam() << std::endl;
            if(i->second->getTeam() == 1)
                team1 += i->first;
            else if(i->second->getTeam() == 2)
                team2 += i->first;
            count++;
        }

        std::cout << "\nTeam ";
        if(team1 > team2)
            std::cout << "1";
        else if(team2 > team1)
            std::cout << "2";
        else
            std::cout << "1 and 2 tied and so both";
        std::cout << " won the tournament." << std::endl;

        std::cout << "Team 1: " << team1 << "\nTeam 2: " << team2 << std::endl;

        delete attacker;
        losers.clear();

        std::cout << "\nDo you want to play another tournament?" << std::endl;
    }while(responseCheck('Y', 'N', '\0', '\0', '\0') == 'Y');

    return 0;
}
