/******************************************************************************
* Author: Jennifer Frase
* Date Created: 10/27/14
* Last Modification Date: 10/30/14
* Filename: recFun.cpp
*
* Overview:
* This program will find the nth number in the Fibonacci sequence.
*
* Input:
* The input will be an int that will be the number n used to find the
* nth number of the Fibonacci sequence.
*
* Output:
* The output for this program will be the nth Fibonacci number.
******************************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

//gets the nth fibonacci number
int fibSeq(int value, int pos);

//gets an integer and makes sure it is valid
int intCheck();

int main()
{
    const int start = 2; //first fibonacci number that uses recursion
    int value; //nth fibonacci number obtained from the user
    int number;//the number at the nth fibonacci number

    cout << "Please give me a number between 0 and 45 inclusive." << endl;
    value = intCheck();
    number = fibSeq(value, start);

    //input was valid so display output
    if (number != 0)
        cout << "\n" << number << " is the " << value;

    //prints appropriate ordinal for number
    if (value == 1)
        cout << "st";
    else if (value == 2)
        cout << "nd";
    else if (value == 3)
        cout << "rd";
    else
        cout << "th";

    cout << " value in the Fibonacci sequence." << endl;

    return 0;
}

/******************************************************************************
* Entry:Two integers, the nth Fibonacci number stored in value, and the second
* is the nth Fibonacci number the function is currently at for values above 1.
*
* Exit: The function will return 0 if the value given is below zero or greater
* than 45. (The value 46 overloads the integer and results in inaccurate numbers
* afterward.)  If value is valid, then the function will calculate the nth
* fibonacci number and return that number.
*
* Purpose: getting the nth fibonacci number
*
******************************************************************************/
int fibSeq(int value, int pos)
{
    const int minValue = 0, maxValue = 45; // boundary numbers for value
    static int firstNum = 1; //stored first value to be added for final sum
    static int secondNum = 1; //stored second value to be added for final sum
    int sum = secondNum; //sum returned

    //control for negative numbers and values greater than 45
    if(value < minValue || value > maxValue)
    {
        cout << "Your value has to be between 0 and 45 inclusive." << endl;
        return 0;
    }


    //if value is greater than one and there is still a Fibonacci number
    //to get, then calculated sum and store in secondNum
    if (value > 1 && pos <= value)
    {
        sum = firstNum + secondNum;
        firstNum = secondNum;
        secondNum = sum;
        sum = fibSeq(value, ++pos);
    }

    return sum;
}

/******************************************************************************
* Entry: none
*
* Exit: gets user input and checks that it is an int, returns input if it is
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

