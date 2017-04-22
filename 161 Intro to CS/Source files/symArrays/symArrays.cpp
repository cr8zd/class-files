/******************************************************************************
* Author: Jennifer Frase
* Date Created: 11/10/14
* Last Modification Date: 11/15/14
* Filename: symArrays.cpp
*
* Overview:
* This program will determine if 3 given rows of integers are symmetric.
*
* Input:
* The input will be 3 integers for the number integers in each rows, and the
* integers in those rows.
*
* Output:
* This program will print whether a row of integers is symmetric. If there
* are not 4 command line arguments, then program will print appropriate
* (too few, too many) error message only.
******************************************************************************/

#include <iostream>
#include <new>
#include <cstdlib>
#include <cstring>
#include <climits>

using namespace std;

//fill the given array with the given number of elements
void arrayFill(int [], int);

//calls isSym to determine what to print
void printSym(int[], int, int);

//returns whether the given array is symmetrical
bool isSym(int [], int);

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        cout << "Too " << (argc < 4? "few" : "many") << " arguments." << endl;
        return 1;
    }

    //get sizes of arrays from command line arguments
    int size1 = atoi(argv[1]);
    int size2 = atoi(argv[2]);
    int size3 = atoi(argv[3]);

    //dynamically allocate arrays to store user input for each row
    int *array1 = new int [size1];
    int *array2 = new int [size2];
    int *array3 = new int [size3];

    //fill arrays skipping '\n' after input
    arrayFill(array1, size1);
    cin.ignore();
    arrayFill(array2, size2);
    cin.ignore();
    arrayFill(array3, size3);

    cout << endl;

    //print if the arrays are symmetrical
    printSym(array1, size1, 1);
    printSym(array2, size2, 2);
    printSym(array3, size3, 3);

    //deallocate arrays
    delete array1;
    array1 = 0;
    delete array2;
    array2 = 0;
    delete array3;
    array3 = 0;

    return 0;
}

/******************************************************************************
* Entry: one integer array and 1 integer which is the size of the array
*
* Exit: gets a row of integers, where the number of integers is the size
* of the array.
*
* Purpose: getting user input
******************************************************************************/
void arrayFill(int arrayCur[], int maxCount)
{
    cout << "Please give " << maxCount << " number"
         <<(maxCount == 1? "" : "s") <<" for the array." << endl;

    //get input and check that there are enough
    for (int i = 0; i < maxCount; i++)
    {
        //if not enough input print error message and force
        //user to redo that array
        if (cin.peek() == '\n')
        {
            cout << "You gave too few numbers." << endl;
            cin.ignore();
            arrayFill(arrayCur, maxCount);
            break;
        }

        cin >> arrayCur[i];
    }

    char next = cin.peek(); //next char in input buffer

    //check for more input since the user did not
    //press enter after last number in array
    if (next != '\n')
    {
        //ignore whitespace
        while (isspace(next) && next != '\n')
        {
            cin.ignore();
            next = cin.peek();
        }

        //there is more input, so empty input stream, print
        //error message and force user to redo that array
        if(next != '\n')
        {
            cin.ignore(INT_MAX, '\n');
            cout << "You gave too many numbers." << endl;
            arrayFill(arrayCur, maxCount);
        }
    }
}

/******************************************************************************
* Entry: one integer array and 2 integers which are the size of the array and
*        the array number
*
* Exit: prints out whether the array is symmetrical
*
* Purpose: printing if the array is symmetrical
******************************************************************************/
void printSym(int arrayCur[], int arraySize, int arrayNumber)
{
    cout << "Array " << arrayNumber << " is "
         << (isSym(arrayCur, arraySize)? "" : "not ") << "symmetric." << endl;
}

/******************************************************************************
* Entry: one integer array and 1 integer which is the size of the array
*
* Exit: checks if the array is symmetrical, returns false if it isn't
*
* Purpose: checking that the array is symmetrical
******************************************************************************/
bool isSym(int arrayCur[], int arraySize)
{
    for (int i = 0; i < arraySize/2.0; i++)
    {
        if (arrayCur[i] != arrayCur[arraySize - 1 - i])//check for symmetry
            return false;
    }

    return true;
}
