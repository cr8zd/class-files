/******************************************************************************
* Author: Jennifer Frase
* Date Created: 10/22/14
* Last Modification Date: 10/22/14
* Filename: randFun.cpp
*
* Overview:
* This program will generate a random number between two given numbers.
*
* Input:
* The input will be two integers
*
* Output:
* The output for this program will be the random number generated.
* If an error occurs main will return INT_MAX.
******************************************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <climits>
#include <cstdio>

using namespace std;

//generates a random number
int rand_int(int min, int max);

//gets a number and checks it is an int
int NumCheck();

//empties the input stream and resets the flags
void CinEmpty();

int main()
{
    int numberMin, numberMax; //user input
    int randNum; //random number generated

    cout << "Please give me a number." << endl;
    numberMin = NumCheck();

    cout << "Please give me a second number." << endl;
    numberMax = NumCheck();

    //swap numbers if numberMin is greater than numberMax
    if (numberMax < numberMin)
    {
        int temp = numberMax;
        numberMax = numberMin;
        numberMin = temp;
    }

    randNum = rand_int(numberMin, numberMax);
    if (randNum == INT_MAX)
        return randNum;

    cout << "The random number generated between " << numberMin
         << " and " << numberMax << " was " << randNum << "." << endl;

    return 0;
}

/******************************************************************************
* Entry: two integers
*
* Exit: gets a random number between min and max and return the number. If
* min is greater than max, returns INT_MAX
*
* Purpose: generating a random number within a given range
*
******************************************************************************/
int rand_int(int min, int max)
{
    int number;
    int range = max - min + 1;

    if (range <= 0)
        return INT_MAX;

    srand(time(0));

    number = rand() % range + min;

    return number;
}

/******************************************************************************
* Entry: none
*
* Exit: gets user input and checks that it is an int, returns input if it is
*
* Purpose: getting and checking validity of input
*
******************************************************************************/
int NumCheck()
{
    int number; //user input
    string junk; //throws input away if not int
    bool error = false; //input was not an int

    //loops while input is not an int
    do
    {
        cin >> number;

        if (cin.fail())
        {
            cout << "Give only integers please." << endl;
            cin.clear();
            getline(cin, junk);
            error = true;
        }
        else
        {
            error = false;
            CinEmpty();
        }

    } while (error);

    return number;
}

/******************************************************************************
* Entry: none
*
* Exit: if there is something in the input stream, gets rid of it
*
* Purpose: refreshing input buffer for transitions between cin and getline
*
******************************************************************************/
void CinEmpty()
{
    if(cin.peek() != EOF)
    {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
}
