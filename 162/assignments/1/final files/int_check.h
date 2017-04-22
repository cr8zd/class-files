/*****************************************************************************************
** Program Filename: int_check.h
** Author: Jennifer Frase
** Date: 1/18/15
** Description: get and check validity of 1 input
** Input: a number between a given range
** Output: none
*****************************************************************************************/
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <climits>
#include <string>
using std::string;
#include <cstdlib>
using std::atoi;

#ifndef INT_CHECK_H_INCLUDED
#define INT_CHECK_H_INCLUDED
/******************************************************************************
* Entry: two integer values used as range parameters for the user input, to
*        not use a range make min greater than max ie intCheck(1,0)
*
* Exit: gets user input and checks that it is a single int, ignores whitespace,
*       and returns input if it is an integer between the given range if a
*       range is given
*
* Purpose: getting and checking validity of 1 input
******************************************************************************/
int intCheck(int min, int max)
{
    string number; //user input
    bool error; //input was not an int in given range
    bool numberThere; //user input had a number
    bool space; //user input had a space after a number

    if (min < max)
    {
        cout << "\nPlease give an integer between " << min << " and " << max
             << "." << endl;
    }

    //loops while input is not a number in given range
    do
    {
        error = false;
        numberThere = false;
        space = false;
        getline(cin, number);

        //check that input is only 1 number, if so error = false, numberThere = true
        for (int i = 0; i < number.length(); i++)
        {
            if(!isdigit(number[i]))
            {
                if (!isspace(number[i]) && number[i] != '-'
                    || (number[i] == '-' && numberThere))
                    error = true; //found nondigit that isn't whitespace
                else if (numberThere && isspace(number[i]) && !space)
                    space = true; //found first space after number
            }
            else
            {
                if (numberThere && space)
                    error = true; //found extra number
                else if (!numberThere)
                    numberThere = true; //found first number character
            }

        }

        //ignore whitespace but if the input is wrong print error message
        if (number.empty() || (!numberThere && !error))
            error = true;
        else if (error)
            cout << "\nPlease give only 1 integer before hitting ENTER." << endl;

        //if valid integer, check that it is in the given range
        if (!error && min < max)
        {
            int num = atoi(number.c_str());
            if (num > max || num < min)
            {
                cout << "\nPlease give an integer between " << min << " and " << max
                     << "." << endl;
                error = true;
            }
        }

    } while (error);

    return atoi(number.c_str());
}


#endif // INT_CHECK_H_INCLUDED
