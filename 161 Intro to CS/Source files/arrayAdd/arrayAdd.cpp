/******************************************************************************
* Author: Jennifer Frase
* Date Created: 11/4/14
* Last Modification Date: 11/9/14
* Filename: arrayAdd.cpp
*
* Overview:
* This program will add together two integer arrays and print the sum of the
* integers at the same indexes in array format.
*
* Input:
* The input will be two separate lists of integers which are stored in arrays.
*
* Output:
* The output for this program will be an array where each index is the sum of
* the corresponding indexes in the two given arrays.
******************************************************************************/

#include <iostream>
#include <cstdlib>
#include <climits>
#include <string>

using namespace std;

//gets input and checks it is an int
int intCheck();

//sums the corresponding indexes in arrays
void sumArrays(const int *, const int *, int *, int);

//fills the arrays with integers
void arrayFill(int *, int);

int main()
{
    const int MAX_SIZE = 50; //max size of arrays
    int set1[MAX_SIZE], set2[MAX_SIZE], //user input lists of integers
        sumSet[MAX_SIZE]; // summed indexes from set1 and set2
    int arraySize; // user input for the number of numbers per array
    int *sums = sumSet; //pointer used to parse through the array for printing

    //get all user input
    cout << "How large are your arrays?" << endl;
    arraySize = intCheck();
    cout << "\nWhen listing integers, please press ENTER after each number." << endl;
    cout << "\nPlease list your first array of integers." << endl;
    arrayFill(set1, arraySize);
    cout << "\nPlease list your second array of integers." << endl;
    arrayFill(set2, arraySize);

    //get summed array and print
    sumArrays(set1, set2, sumSet, arraySize);
    cout << "\nYour arrays added together are:\n[";

    for (int i = 0; i < arraySize; i++)
    {
        cout << *sums << (arraySize - i != 1? ", " : "]");
        sums++;
    }

    return 0;
}

/******************************************************************************
* Entry: three pointers to arrays and one integers which is the size of all the
*        arrays given. The first two arrays are user input and the third is the
*        storage array for this function.
*
* Exit: sums corresponding indexes in set1 and set2, and then stores that value
*       in the corresponding index of sumSet.
*
* Purpose: summing the corresponding indexes of two arrays
*
******************************************************************************/
void sumArrays(const int *set1, const int *set2, int *sumSet, int arraySize)
{
    for(int i = 0; i < arraySize; i++)
    {
        *sumSet = *set1 + *set2;
        sumSet++;
        set1++;
        set2++;
    }
}

/******************************************************************************
* Entry: one pointer to an array and one integer which is the size of the array
*
* Exit: gets arraySize number of integers and stores them in numbers
*
* Purpose: filling a given array of a given size with integers
*
******************************************************************************/
void arrayFill(int *numbers, int arraySize)
{
    int num; //a single user input

    for(int i = 0; i < arraySize; i++)
    {
        num = intCheck();
        *numbers = num;
        numbers++;
    }
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
            cout << "Please give only 1 integer before hitting ENTER." << endl;

        //ignore enter presses
        if (number.empty())
            error = true;

    } while (error);

    return atoi(number.c_str());
}
