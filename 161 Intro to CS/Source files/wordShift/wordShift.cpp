/******************************************************************************
* Author: Jennifer Frase
* Date Created: 11/4/14
* Last Modification Date: 11/9/14
* Filename: wordShift.cpp
*
* Overview:
* This program will take a c-string and allow the user to pick from 4 commands
* where the first three will alter the given string and the last allows the
* user to exit.
*
* Input:
* The input will be a c-string and string commands on what to do next
*
* Output:
* The output for this program will be the given string altered based on the
* command given, where rev will reverse the string, and L(x) or R(x) will shift
* the letters over left or right respectively.
******************************************************************************/

#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <climits>

using namespace std;

//reverse the given c-string
void reverseString(char [], int, int);

//shift the letters to the right
void shift(char [], int, int);

//checks that the given string can be converted to an int
int intCheck(string);

const int MAX_SIZE = 30; // max size for c-strings

int main()
{
    string com; //user input for command
    char phrase[MAX_SIZE]; //user input for string that will be manipulated
    bool isCommand; //true if com is a valid command
    int phraseSize; //size of user input c-string

    //get string to mix
    cout << "Please enter a string" << endl;
    cin.getline(phrase, MAX_SIZE);
    phraseSize = strlen(phrase);

    cout << "\nPossible commands are: rev, R(x), L(x), and quit."
         << "\nThe (x) in R(x) and L(x) is a positive integer less than "
         << INT_MAX << "." << endl;

    //loop until quit is entered
    do
    {
        isCommand = true;
        cout << "Please enter a command." << endl;
        getline(cin, com);

        //check that command is one of 4 valid commands
        if(com == "rev") //reverse string
        {
            reverseString(phrase, phraseSize - 1, 0);
        }
        else if (com[0] == 'R' || com[0] == 'L') //shift string to the right
        {
            char letter = com[0]; //first letter of command
            com.erase(com.begin());
            int value = intCheck(com) % phraseSize; //equivalent value after first letter
                                                    //-1 if not integer after first letter
            //shift letters over if a nonnegative integer is returned from intCheck
            if (value >= 0)
                shift(phrase, phraseSize, (letter == 'R'? value : phraseSize - value));
            else
                isCommand = false;
        }
        else if (com == "quit") //quit program
        {
            continue;
        }
        else
        {
            isCommand = false;
        }

        //Print string with appropriate sentence
        if (isCommand)
        {
            cout << "New string: ";
        }
        else
        {
            cout << "Invalid command." << endl;
            cout << "Your string is: ";
        }

        cout << phrase << endl;
    } while (com != "quit");
    return 0;
}

/******************************************************************************
* Entry: one c-string and two integers, where the first is the index of the
*        last letter in the c-string and the second is a counter for the number
*        of times to repeat (initial call should be 0).
*
* Exit: exchanges characters based on their position in the string where the
*       first and last are exchanged, then the second and next to last, and
*       so on until the word is reversed.
*
* Purpose: reversing the given c-string
*
******************************************************************************/
void reverseString(char cstring[], int lastLetter, int counter)
{
    if(lastLetter > counter * 2)
    {
        char temp = cstring[counter]; //temporary storage for a letter
        cstring[counter] = cstring[lastLetter - counter];
        cstring[lastLetter - counter] = temp;
        reverseString(cstring, lastLetter, ++counter);
    }
}

/******************************************************************************
* Entry:a c-string and two integers where the first is the size of the c-string
*       and the second is a counter for the number of times the function should
*       repeat
*
* Exit:loops through the characters in the c-string and shifts them to the left
*      before repeating as long as the counter is greater than 0
*
* Purpose: shifting letters to the right a given number of times
*
******************************************************************************/
void shift(char cstring[], int stringSize, int counter)
{
    char temp[MAX_SIZE]; // copy of original for shifting letters

    for (int i = 0; i < stringSize; i++)
    {
        temp[i] = cstring[i];
    }

    //shift letters
    for(int i = 0; i < stringSize; i++)
    {
        cstring[(i + counter) % stringSize] = temp[i];
    }
}

/******************************************************************************
* Entry: a string
*
* Exit: checks that the given string is an integer, returns input as an
*       integer if it is, if not returns -1
*
* Purpose: getting and checking validity of input
*
******************************************************************************/
int intCheck(string number)
{
    //check that all characters are numbers
    for (int i = 0; i < number.length(); i++)
    {
        if(!isdigit(number[i]))
            return -1;
    }

    return atoi(number.c_str());
}
