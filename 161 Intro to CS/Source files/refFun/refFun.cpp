/******************************************************************************
* Author: Jennifer Frase
* Date Created: 10/28/14
* Last Modification Date: 10/30/14
* Filename: refFun.cpp
*
* Overview:
* This program will compare two strings and print if they are the same.
*
* Input:
* The input will be two strings.
*
* Output:
* The output for this program will be if the strings are the same.
******************************************************************************/

#include <iostream>
#include <string>

using namespace std;

//compares two strings
int compareStr(string &phrase1, string &phrase2);

int main()
{
    string phrase1, phrase2;//user input
    int same; //returned value from compareStr, 0 if same

    //get input
    cout << "Please give me a phrase." << endl;
    getline(cin, phrase1);
    cout << "\nPlease give me a phrase." << endl;
    getline(cin, phrase2);

    //compare and print results
    same = compareStr(phrase1, phrase2);
    cout << "\nYour phrases were "
         << (same == 0? "the same." : "different.")
         << endl;

    return 0;
}

/******************************************************************************
* Entry: Two references to strings.
*
* Exit: Compares each character in the strings. If the strings are not the
* same length or characters are not the same, then 1 is returned, otherwise
* 0 is returned.
*
* Purpose: comparing two strings
******************************************************************************/
int compareStr(string &phrase1, string &phrase2)
{
    if (phrase1.length() != phrase2.length())
        return 1;

    for (int i = 0; i < phrase1.length(); i++)
    {
        if (phrase1[i] != phrase2[i])
            return 1;
    }

    return 0;
}
