/******************************************************************************
* Author: Jennifer Frase
* Date Created: 11/10/14
* Last Modification Date: 11/15/14
* Filename: sameSum.cpp
*
* Overview:
* This program will compare the values of a given grid of integers to see if
* all the rows, columns, and diagonals have the same sum.
*
* Input:
* The input will be an integer for the size of a grid of numbers and the
* integers that fill that grid.
*
* Output:
* The output for this program will be either "true" or "false" depending on
* whether the sums of all rows, columns, and diagonals are the same.
******************************************************************************/

#include <iostream>
#include <cstdlib>
#include <new>

using namespace std;

const int MAX_SIZE = 10; //max size of array

//checks if array's rows, columns, and diagonals have the same sum
bool gridOK(int [] [MAX_SIZE], int);

//get and check that input is an integer
int intCheck(int, int);

int main()
{
    int grid [MAX_SIZE] [MAX_SIZE];//user input
    int rows;//number of line of user input as well as the number of number per line

    cout << "How many rows do you want?" << endl;
    rows = intCheck(0, MAX_SIZE);

    //fill array with values
    for (int i = 0; i < rows; i++)
    {
        cout << "\nPlease give " << rows << " number"
            << (rows == 1? "" : "s") <<" in row " << i << ":" << endl;
        for(int j = 0; j < rows; j++)
        {
            cin >> grid[i][j];
        }
    }

    //print result
    if (gridOK(grid, rows))
        cout << "\ntrue" << endl;
    else
        cout << "\nfalse" << endl;

    return 0;
}

/******************************************************************************
* Entry: one integer 2d array and 1 integer which is the number of row in the
*        2d array
*
* Exit: checks to see if all rows/columns/diagonals have the same value, if
*       they do, returns true
*
* Purpose: checking that all rows/column/diagonals have the same sum
******************************************************************************/
bool gridOK(int grid [] [MAX_SIZE], int rows)
{
    int *sums = new int [rows * 2 + 2]; //storage for the sums of the rows/
                                        //columns/diagonals
    //initialize sums
    for (int i =0; i < rows * 2 + 2; i++)
    {
        sums[i] = 0;
    }

    //put the sums of rows/columns/diagonals in appropriate index
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            sums[i] += grid[i][j]; //rows
            sums[j+rows] += grid[i][j]; //columns
            if (i == j)
                sums[rows *2] += grid[i][j]; //backslash diagonal
            if (i + j == rows - 1)
                sums[rows * 2 + 1] += grid[i][j]; //forward slash diagonal
        }
    }

    //check that all values equal the first rows sum
    for (int i = 1; i < rows * 2 + 2; i ++)
    {
        if (sums[0] != sums[i])
        {
            delete sums;
            sums = 0;
            return false;
        }
    }

    delete sums;
    sums = 0;
    return true;
}

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
            if(!isdigit(number[i]) && !isspace(number[i]))
                error = true; //found non digit that isn't whitespace

            else if (!isdigit(number[i]) && numberThere &&
                     isspace(number[i]) && !space)
                space = true; //found first whitespace after a number

            else if (isdigit(number[i]) && numberThere && space)
                error = true; //found extra number

            else if (isdigit(number[i]) && !numberThere)
                numberThere = true; //found first number character
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
