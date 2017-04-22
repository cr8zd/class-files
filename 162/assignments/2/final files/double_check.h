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
using std::atof;
using std::showpoint;
#include <iomanip>
using std::setprecision;

#ifndef DOUBLE_CHECK_H_INCLUDED
#define DOUBLE_CHECK_H_INCLUDED

/******************************************************************************
* Entry: two double values used as range parameters for the user input, to
*        not use a range make min greater than max ie doubleCheck(1,0), as well
*        as an integer which represents the number of numbers after the decimal
*        point, to void this make it negative ie doubleCheck(,,-1)
*
* Exit: gets user input and checks that it is a single double with a precision
*       of maxCount after the decimal, ignores whitespace, and returns input if
*       it is a double between the given range if a range is given
*
* Purpose: getting and checking validity of 1 input
******************************************************************************/
double doubleCheck(double min, double max, int maxCount)
{
    string number; //user input
    int decimalCount; //number of numbers after decimal
    bool error; //input was not an int in given range
    bool numberThere; //user input had a number
    bool space; //user input had a space after a number
    bool decimal; //user input had a decimal

    //loops while input is not a number in given range
    do
    {
        decimalCount = 0;
        error = false;
        numberThere = false;
        space = false;
        decimal = false;
        getline(cin, number);

        //check that input is only 1 number, if so error = false,
        //numberThere = true
        for (int i = 0; i < number.length(); i++)
        {
            if (!isdigit(number[i]))
            {
                if (!decimal && number[i] == '.' && numberThere)
                    decimal = true; // found first period

                else if(!isspace(number[i]) && number[i] != '-' //found invalid char
                        || (!decimal && number[i] == '.' && !numberThere) //period before a digit
                        || (decimal && number[i] == '.') //a second period
                        || (number[i] == '-' && numberThere) //a negative after a digit
                        || (number[i] == '-' && i + 1 != number.length()
                            && !isdigit(number[i + 1]))) //negative is not before a digit

                    error = true;

                else if (numberThere && isspace(number[i]) && !space)
                    space = true; // found first space after number char
            }
            else
            {
                if (numberThere && space)
                    error = true; //found extra number
                else if (!numberThere)
                    numberThere = true; //found first number char
                else if (decimal && numberThere && !space)
                    decimalCount++;
            }
        }

        if (maxCount > 0 && decimalCount != maxCount)
            error = true;

        //ignore whitespace but if the input is wrong print error message
        if (number.empty() || (!numberThere && !error))
        {
            error = true;
        }
        else if (error)
        {
            cout << "\nPlease give only 1 double";

            if(maxCount > 0) //only ask for a specific form if maxCount is valid
            {
                cout << " of the form x.";
                for(int i = 0; i < maxCount; i++)//maxCount number of z's
                {
                    cout << "z";
                }
                cout << ", where x is any \ninteger and z is any"
                     << " digit";
            }
            cout << ", before hitting ENTER." << endl;
        }

        //if valid integer, check that it is in the given range
        if (!error && min < max)
        {
            int num = atof(number.c_str());
            if (num > max || num < min)
            {
                cout << setprecision(2) << showpoint;
                cout << "\nPlease give a double between " << min << " and "
                     << max << "." << endl;
                error = true;
            }
        }

    } while (error);

    return atof(number.c_str());
}


#endif // DOUBLE_CHECK_H_INCLUDED
