/******************************************************************************
* Author: Jennifer Frase
* Date Created: 11/4/14
* Last Modification Date: 11/6/14
* Filename: stringMix.cpp
*
* Overview:
* This program will take a given string and mix it any number of times until
* the user does not want another mix of the original string.
*
* Input:
* The input will be a single string that the program will mix.
*
* Output:
* The output for this program will be a random mixture of the characters in
* the original string.
******************************************************************************/

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <climits>

using namespace std;

//randomizes letters in a c-string
void strMix(const char [], char []);

//gets input and makes sure it is valid
char responseCheck(char , char , char );

int main()
{
    const int arraySize = 10; //max size of array
    char phrase[arraySize], //user input
         phraseMix[arraySize]; //mixed up user input
    char response; //response, y if user want another mix up

    srand(time(0));
    cout << "Please give me a phrase." << endl;
    cin.getline(phrase, arraySize);

    //loop till the user wants to quit
    do
    {
        //get mixed string and print
        strMix(phrase, phraseMix);
        cout << "\nYour phrase, " << phrase << ", was mixed up and is now ";
        for(int i = 0; i < strlen(phrase); i++)
        {
            cout << phraseMix[i];
        }
        cout << "." << endl;

        //ask if they want another arrangement
        cout << "\nDo you want another arrangement?" << endl;
        response = responseCheck('Y', 'N', '\0');
    }while (response == 'Y');

    return 0;
}

/******************************************************************************
* Entry: Two c-strings, where the first is the given string and the second is
*        the mixed up string that is the end product of this function.
*
* Exit: stores the given string in the second string and then mixes two
*       characters up n number of times, where n is the length of the string.
*
* Purpose: randomizing the letters in the given string.
*
******************************************************************************/
void strMix(const char phrase[], char phraseMix[])
{
    int length = strlen(phrase); //length of the c-string user input

    //assign the letters in phrase to phraseMix
    for(int i = 0; i < length; i++)
    {
        phraseMix[i] = phrase[i];
    }

    //loop once per character in phraseMix and switch current letter
    //with a random letter
    for(int i = 0; i < length; i++)
    {
        int replaceTo = rand() % length; //random spot to replace
        char temp = phraseMix[replaceTo]; //temporary storage of character
        phraseMix[replaceTo] = phraseMix[i];
        phraseMix[i] = temp;
    }
}

/******************************************************************************
* Entry: Three char values for which the function can check against, can be
*        '\0', and letter values should be uppercase
*
* Exit: gets user input and compares it to the valid responses until it final
*       gets a valid response
*
* Purpose: checking that a response is valid
*
******************************************************************************/
char responseCheck(char valid1, char valid2, char valid3)
{
    char response = '\0'; //user input

    //checks user input against given valid characters
    while(response != valid1 && response != valid2
            && ((valid3 == '\0')? true : response != valid3))
    {
        //print options
        cout << "Please enter only: " << valid1 << " or " << valid2;
        if (valid3 != '\0')
            cout << " or " << valid3;
        cout << endl;

        cin.get(response);

        if(response != '\n')
            cin.ignore(INT_MAX, '\n');

        if(isalpha(response))
            response = toupper(response);
    }

    cout << endl;

    return response;
}

