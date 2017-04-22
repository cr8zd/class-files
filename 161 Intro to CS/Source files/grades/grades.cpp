/******************************************************************************
* Author: Jennifer Frase
* Date Created: 11/4/14
* Last Modification Date: 11/6/14
* Filename: grades.cpp
*
* Overview:
* This program will take any number of grades (0 - 5) and print how many of
* each grade there was.
*
* Input:
* The input will be any number of integers separated by spaces which represent
* the grades of the students given from 0 - 5.
*
* Output:
* The output for this program will be a the list of how many of each grade
* where given.
******************************************************************************/

#include <iostream>
#include <istream>
#include <cstdio>

using namespace std;

bool isValid(int number);

int main()
{
    int studentGrades[6] = {0}; //the list of possible grades (0 - 5)

    cout << "Please list the grades with a space in between each grade."
         << "\nHit ENTER to stop inputting grades." << endl;

    while(cin.peek() != '\n')
    {
        int num; //a single integer in the input stream
        cin >> num;

        if (cin.fail())
        {
            cout << "You didn't give me integers only." << endl;
            return -1;
        }

        //checks that integers is in the proper range
        //if so then increments the appropriate number
        if (isValid(num))
        {
            studentGrades[num]++;
        }
    }

    for (int i = 0; i < 6; i++)
    {
        cout << studentGrades[i] << " grade(s) of " << i << endl;
    }

    return 0;
}

/******************************************************************************
* Entry: One integer
*
* Exit: checks that the integer is between 0 and 5 inclusive, return true if it
*       is
*
* Purpose: checking that a number is in the range of possible grades
******************************************************************************/
bool isValid(int number)
{
    bool valid = false; //true if number is between 0 and 5 inclusive

    if (number >= 0 && number <= 5)
        valid = true;

    return valid;
}
