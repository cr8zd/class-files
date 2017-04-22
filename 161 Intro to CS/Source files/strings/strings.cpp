/******************************************************************************
* Author: Jennifer Frase
* Date Created: 10/16/14
* Last Modification Date: 10/18/14
* Filename: strings.cpp
*
* Overview:
* This program will play with a user input string. It will print
* the string forwards and backwards, then it will print how many
* letters are in the word.
*
* Input:
* The input will be a string that the user makes up.
*
* Output:
* The output for this program will be the users string
* forward and backward. After printing the the string is will
* say how many letters are in the string.
******************************************************************************/

#include <iostream>
#include <string>

using namespace std;

int main()
{
    string userInput;
    int letters = 0;

    while (userInput.empty())
    {
        cout << "Please give me a word." << endl;
        getline(cin, userInput);
        if (userInput.empty())
            cout << "Do not just press enter!" << endl;
    }

    for (unsigned i = 0; i < userInput.length(); i++)
    {
        cout << userInput.at(i);
        if (toupper(userInput.at(i)) >= 'A' && toupper(userInput.at(i)) <= 'Z')
            letters++;
    }

    cout << endl;

    for (int i = (userInput.length() - 1); i >= 0; i--)
    {
        cout << userInput.at(i);
    }

    cout <<  endl;
    cout << "There are " << letters << " letters in this word." << endl;

    return 0;
}
