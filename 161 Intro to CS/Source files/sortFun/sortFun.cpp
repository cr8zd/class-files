/******************************************************************************
* Author: Jennifer Frase
* Date Created: 10/28/14
* Last Modification Date: 10/30/14
* Filename: sortFun.cpp
*
* Overview:
* This program will sort three given integers from lowest to highest.
*
* Input:
* The input will be three integers.
*
* Output:
* The output for this program will be the sorted integers from lowest to
* highest.
******************************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

//sorts given ints
void sortInt(int &low, int &mid, int &high);

//gets and checks that user input is an int
int intCheck();

int main()
{
    int low, mid, high;//user input

    //get and check input
    cout << "Please give me three numbers seperate by "
         << "spaces or enter presses." << endl;
    low = intCheck();
    mid = intCheck();
    high = intCheck();

    //sort and display input
    sortInt(low, mid, high);
    cout << "\nThe three numbers you gave are now sortInted "
         << "from low to high:\n" << low << ", " << mid
         << ", " << high << endl;

    return 0;
}

/******************************************************************************
* Entry: three references to three integers
*
* Exit: sorts the given integers from lowest to highest by swapping any values
* that are out of place.
*
* Purpose: rearranging the values of the integers so that the first variable
* has the lowest value and the last variable has the highest value
******************************************************************************/
void sortInt(int &low, int &mid, int &high)
{
    if (low > high)
    {
        low += high;
        high = low - high;
        low -= high;
    }

    if (low > mid)
    {
        low += mid;
        mid = low - mid;
        low -= mid;
    }

    if (mid > high)
    {
        mid += high;
        high = mid - high;
        mid -= high;
    }
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
