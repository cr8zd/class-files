/******************************************************************************
* Author: Jennifer Frase
* Date Created: 10/28/14
* Last Modification Date: 10/30/14
* Filename: hailstone.cpp
*
* Overview:
* This program will print the number of steps it takes to reach 1 given a
* users number and the rules that even numbers are divided by 2, and odd
* numbers are multiplied by 3 then 1 is added.
*
* Input:
* The input will be a singe integer.
*
* Output:
* The output for this program will be the number of steps it took to reach 1.
******************************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>
#include <climits>

using namespace std;

//counts number of steps to reach 1
int hail(int num);

//gets and checks that input is an int
int intCheck();

int main()
{
    int num, //user input
        steps; //number of steps returned from hail()

    cout << "Please give me a number" << endl;
    num = intCheck();
    steps = hail(num);

    if (steps >= 0)
        cout << "\nThe number of steps it took to reach 1 was "
             << steps << "." << endl;
    else
        cout << "\nNumbers must be greater than 0." << endl;

    return 0;
}

/******************************************************************************
* Entry: a single integer which is the starting value
*
* Exit: returns INT_MIN if input is invalid, returns 0 if num is 1, otherwise
* it calculates the number of steps it takes to reach 1 given that even numbers
* are divided in half and odd numbers are tripled and 1 is added.
*
* Purpose: getting the number of steps to reach 1
*
******************************************************************************/
int hail(int num)
{
    //base case 0 and below invalid number return negative
    if (num < 1)
        return INT_MIN;
    else if (num == 1) // base case 1 return no steps
        return 0;
    else if (num % 2 == 1) // odd number above 1
        return 1 + hail(num * 3 + 1);
    else // even number
        return 1 + hail(num / 2);
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
