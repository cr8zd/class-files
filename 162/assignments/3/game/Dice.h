#include <cstdlib>
#include <ctime>

#ifndef DICE_H_INCLUDED
#define DICE_H_INCLUDED
class Dice
{
public:   Dice();
          Dice( int numSides);
          virtual int rollDice() const;
protected:
          int numSides;
};

Dice::Dice()
{
    numSides = 6;
    srand(time(NULL)); // Seeds random number generator
}
Dice::Dice(int numSides)
{
    this->numSides = numSides;
    srand(time(NULL)); // Seeds random number generator
}

int Dice::rollDice() const
{   return (rand() % numSides) + 1; } // Take two dice objects, roll them, and return the sum

int rollTwoDice(const Dice& die1, const Dice& die2)
{   return die1.rollDice() + die2.rollDice(); }

#endif // DICE_H_INCLUDED
