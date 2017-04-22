/******************************************************************************
* Author: Jennifer Frase
* Date Created: 10/17/14
* Last Modification Date: 10/17/14
* Filename: loop.cpp
*
* Overview:
* This program will take a two user statements and compare
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
#include <string>

using namespace std;

int main()
{
    string phrase1, phrase2; // two user inputs, can be anything
    bool same = true; // were the inputs the same

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

    // if they are the same length, check contents
    if (phrase1.length() != phrase2.length())
    {
        same = false;
    }
    else
    {
        for (int i = 0; i < phrase1.length(); i ++)
        {
            if (phrase1[i] != phrase2[i])
                same = false;
        }
    }

    cout << "\nYour phrases were " << (same? "" : "not ")
         << "the same." << endl;

    return 0;
}
