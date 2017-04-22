/******************************************************************************
* Author: Jennifer Frase
* Date Created: 11/18/14
* Last Modification Date: 11/22/14
* Filename: findMode.cpp
*
* Overview:
* This program will take a line of integers and find the modes of those
* integers.
*
* Input:
* The input will be a line of integers.
*
* Output:
* The output for this program will be the a list of the most common integers
* in the user's input.
******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//finds the modes of the vector
vector<int> getModes(vector<int>);

//fills a vector with the integers in the string
void fillVector(vector<int> &, string &);

int main()
{
    vector<int> numbers; //storage for user input
    string numberLine; //user input
    bool error; //true if user input is not only integers and whitespace
    bool numberThere; //true if user input has a digit

    cout << "Please enter any number of integers." << endl;

    //get user input and repeat if there is an error
    do
    {
        numberThere = false;
        error = false;

        cout << "Hit ENTER when you are done." << endl;
        getline(cin, numberLine);

        //check if user input is only integers and whitespace
        for (int i = 0; i < numberLine.length(); i++)
        {
            //if it isn't a number or whitespace then line isn't valid
            if(!isdigit(numberLine[i]) && !isspace(numberLine[i]) && numberLine[i] != '-'
               || (numberLine[i] == '-' && i != 0 && numberLine[i - 1] != ' '))
                error = true;
            else if(isdigit(numberLine[i]))
                numberThere = true;
        }

        //no number in input
        if (!numberThere)
            error = true;

        if (error)
            cout << "\nPlease enter a line of ONLY integers seperated "
                 << "by whitespace." << endl;
    } while(error);

    fillVector(numbers, numberLine);
    sort(numbers.begin(), numbers.end());
    vector<int> modeNum = getModes(numbers);

    cout << "\nThe mode" << (modeNum.size() == 1? "" : "s")
         << " for the integers you input " << (modeNum.size() == 1? "is:" : "are:")
         << endl;

    //Print modes
    for (int i = 0; i < modeNum.size(); i++)
    {
        cout << modeNum[i];
        if (i + 1 != modeNum.size())
            cout << ", ";
    }

    cout << endl;
    return 0;
}

/******************************************************************************
* Entry: There is one parameter, a vector of integers.
*
* Exit: loops through all ints and finds the numbers that repeat and adds it
*       to a temp vector. This will repeat recursively till the temp vector
*       has no duplicates
*
* Purpose: getting the modes of a vector of integers
******************************************************************************/
vector<int> getModes(vector<int> modes)
{
    vector<int> temp; //temp storage for duplicates
    bool dup = false; //true if found duplicates

    //loop to find duplicates - taken from the code by John Christiansen
    for(int i = 0; i < modes.size() - 1; i++)
    {
        if(modes[i] == modes[i + 1])
        {
            temp.push_back(modes[i]);
            dup = true;
        }
    }

    //duplicates so check for more
    if(dup)
    {
        modes = getModes(temp);
        temp.clear();
    }


    return modes;
}

/******************************************************************************
* Entry: There are two parameters, the first is a vector of ints, and the
*        second is a string of numbers separated by whitespace
*
* Exit: erases leading whitespace and adds the first number to the vector
*       then uses recursion to repeat until the string is empty
*
* Purpose: Filling the vector with the integers in the string
******************************************************************************/
void fillVector(vector<int> &numbers, string &numberLine)
{
    //erase leading whitespace
    while(!numberLine.empty() && isspace(numberLine[0]))
    {
        numberLine.erase(numberLine.begin());
    }

    //add the first integer in the string to the vector and repeat
    if(!numberLine.empty())
    {
        numbers.push_back(atoi(numberLine.c_str()));

        //erase the chars until numberLine is empty or finds a whitespace
        while(!numberLine.empty() && !isspace(numberLine[0]))
        {
            numberLine.erase(numberLine.begin());
        }

        fillVector(numbers, numberLine);
    }
}
