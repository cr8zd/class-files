/******************************************************************************
* Author: Jennifer Frase
* Date Created: 10/28/14
* Last Modification Date: 10/30/14
* Filename: randFun.cpp
*
* Overview:
* This program will print a random number between a given range of integers.
*
* Input:
* The input will be two integers that will represent the range for the random
* number.
*
* Output:
* The output for this program will be the random number in the given range.
******************************************************************************/
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

//gets a random number
void rand_int(const int &min, const int &max, int &val);

//checks gets input and checks it is a number truncates if not int
int intCheck();

int main()
{
    int minGiven, maxGiven,// user input for the range
        val = 0; //initialization for the random number

    cout << "Please give me a number" << endl;
    minGiven = intCheck();

    cout << "\nPlease give me a another number" << endl;
    maxGiven = intCheck();

    //if minGiven is greater than maxGiven, exchange values
    if (minGiven > maxGiven)
    {
        maxGiven += minGiven;
        minGiven = maxGiven - minGiven;
        maxGiven = maxGiven - minGiven;
    }

    rand_int(minGiven, maxGiven, val);
    cout << "\nThe random number generated between " << minGiven
         << " and " << maxGiven << " is " << val << "." << endl;

    return 0;
}

/******************************************************************************
* Entry: Three integers, the two constants,min and max, represent the minimum
* and maximum values that the random number can be, and the third integer is
* for storing the random number.
*
* Exit: seeds the random function with time(0) and then gets a random number
* between the min and max storing it in val.
*
* Purpose: getting a random number between a given min and max
*
******************************************************************************/
void rand_int(const int &min, const int &max, int &val)
{
    srand(time(0));
    val = rand() % (max - min + 1) + min;
}

/******************************************************************************
* Entry: none
*
* Exit: gets user input and checks that it is a number, returns input if it is
*
* Purpose: getting and checking validity of input
*
******************************************************************************/
int intCheck()
{
    string number; //user input
    string junk; //throws input away if not int
    bool error; //input was not an int

    //loops while input is not a number
    do
    {
        error = false;
        getline(cin, number);

        for (int i = 0; i < number.length(); i++)
        {
            if(!isdigit(number[i]))
                error = true;
        }

        if (error)
            cout << "Please give integers." << endl;

        //ignore enter presses
        if (number.empty())
            error = true;

    } while (error);

    return atoi(number.c_str());
}
