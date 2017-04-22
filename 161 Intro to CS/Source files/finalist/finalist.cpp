/******************************************************************************
* Author: Jennifer Frase
* Date Created: 10/22/14
* Last Modification Date: 10/24/14
* Filename: finalist.cpp
*
* Overview:
* This program will pick a certain number of winners from a certain
* number of participants.
*
* Input:
* There is no input.
*
* Output:
* The output for this program will be the random numbers of the winners.
******************************************************************************/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <new>

using namespace std;

const int winners = 4; // number of winners

void PrintList(int userList[winners]);

int main()
{
    const int participants = 25; // number of participants
    int picked[winners]; //array used to store winning numbers
    int number; //random number

    srand(time(0));

    for (int i = 0; i < winners; i++)
    {
        int round = i; //used to make sure i wasn't adjusted
        number = rand() % participants + 1;

        //loop through current picked number and make sure
        //the random number isn't already in the array
        for (int j = 0; j < winners; j++)
        {
            if (number == picked[j])
                i--;
        }

        //check that i was not decremented
        if (round == i)
            picked[i] = number;
    }

    cout << "The winners were:" << endl;
    PrintList(picked);
    cout << endl;

    return 0;
}

/******************************************************************************
* Entry: an int array
*
* Exit: Separate and print each integer in userList
*
* Purpose: Display the integers in userList
*
******************************************************************************/
void PrintList(int userList[winners])
{
    for(int i = 0; i < winners; i++)
    {
        cout << left << setw(4) << userList[i];

        //creates new line ever 7th character
        //left this line in case winners is increased about 7
        if ((i + 1) % 7 == 0)
            cout << endl;
    }
}
