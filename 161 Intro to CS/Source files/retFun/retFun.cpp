/******************************************************************************
* Author: Jennifer Frase
* Date Created: 10/22/14
* Last Modification Date: 10/22/14
* Filename: retFun.cpp
*
* Overview:
* This program will take two user statements and compare
* them to see if they are the same thing.
*
* Input:
* The input will be two strings. It can be whatever the user
* wants.
*
* Output:
* The output for this program will be whether the two
* strings are the same.
******************************************************************************/

#include <iostream>

using namespace std;

//compares the first string to the second
int Same(string first, string second);

int main()
{
    int different; //value returned by Same function
    string phrase1, phrase2; //user input

    // get inputs
    cout << "Tell me something." << endl;
    getline(cin, phrase1);

    cout << "\nTell me something else, and I will tell"
         << "\nyou if it matches what you told me before" << endl;
    getline(cin, phrase2);

    // check neither input is empty
    while (phrase2.empty() || phrase1.empty())
    {
        if (phrase1.empty())
        {
            cout << "\nThe first line you gave me was empty."
                 << "\nPlease tell me something." << endl;
            getline(cin, phrase1);
        }

        if (phrase2.empty())
        {
            cout << "\nThe second line you gave was empty."
                 << "\nI can't compare it unless you tell me"
                 << "\nsomething." << endl;
            getline(cin, phrase2);
        }
    }


    different = Same(phrase1, phrase2);

    //prints if strings were the same or not
    if (different == 0)
        cout << "\nYour strings were the same." << endl;
    else
        cout << "\nYour strings were different." << endl;

    return 0;
}

/******************************************************************************
* Entry: two strings
*
* Exit: compares the length and contents of the given strings, returns 0 if
* they are the same and 1 if they are different.
*
* Purpose: checking that first and second are the same
*
******************************************************************************/
int Same(string first, string second)
{
    int diffChar = 0;

    // if they are the same length, check contents
    if (first.length() != second.length())
    {
        diffChar = 1;
    }
    else
    {
        for (int i = 0; i < first.length(); i ++)
        {
            if (first[i] != second[i])
                diffChar = 1;
        }
    }

    return diffChar;
}
