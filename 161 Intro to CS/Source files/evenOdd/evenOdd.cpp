/******************************************************************************
* Author: Jennifer Frase
* Date Created: 11/4/14
* Last Modification Date: 11/9/14
* Filename: evenOdd.cpp
*
* Overview:
* This program will take a given number of integers and find the difference
* between the even number and the odd numbers.
*
* Input:
* The input will be a user defined number of integers.
*
* Output:
* The output for this program will be the difference between the even input
* values and the odd input values.
******************************************************************************/

#include <iostream>
#include <cstdlib>

using namespace std;

//gets the difference between the even and odd numbers
int evenDifOdd (int num[], int arraySize);

//gets and checks that user input is an integer
int intCheck();

int main()
{
    int num[50]; //array of integers
    int arraySize, //size of user input stored in num[]
        difSum; //difference between even and odd numbers

    cout << "How many numbers do you want to input?" << endl;
    arraySize = intCheck();
    cout << "\nPlease input " << arraySize << " number"
         << (arraySize == 1? "" : "s")
         << " seperated by ENTER presses." << endl;

    //fill the array with the given number of integers
    for (int i = 0;i < arraySize; i++)
    {
        num[i] = intCheck();
    }

    difSum = evenDifOdd(num, arraySize);

    cout << "\nThe sum of the evens minus the sum of the odds"
         << " is:\n" << difSum << endl;

    return 0;
}

/******************************************************************************
* Entry: one integer array and one integer which is the number of integer in
*        the array
*
* Exit: adds all the even numbers together and the odd numbers together, and
*       returns the difference between those sums
*
* Purpose: getting the difference between all the even and odd numbers
*
******************************************************************************/
int evenDifOdd (int num[], int arraySize)
{
    int even = 0, //even numbers' sum
        odd = 0; //odd numbers' sum

    for (int i = 0; i < arraySize; i++)
    {
        (num[i] % 2 == 0? even: odd) += num[i];
    }

    return even - odd;
}

/******************************************************************************
* Entry: none
*
* Exit: gets user input and checks that it is an integer, returns input if it is
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

        //check that all characters are numbers
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
