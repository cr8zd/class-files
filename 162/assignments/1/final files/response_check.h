/*****************************************************************************************
** Program Filename: response_check.h
** Author: Jennifer Frase
** Date: 1/18/15
** Description: get and check validity of 1 input
** Input: a character from a given list
** Output: none
*****************************************************************************************/
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <climits>

#ifndef RESPONSE_CHECK_H_INCLUDED
#define RESPONSE_CHECK_H_INCLUDED

/******************************************************************************
* Entry: Four char values for which the function can check against, can be
*        '\0' for all but first and letters must be capitalized
*
* Exit: gets user input and compares it to the valid responses until it finally
*       gets a valid response
*
* Purpose: checking that a response is valid
*
******************************************************************************/
char responseCheck(char valid1, char valid2, char valid3, char valid4)
{
    char response = '\0'; //user input

    //checks user input against given valid characters
    while(response != valid1
          && ((valid2 == '\0')? true : response != valid2)
          && ((valid3 == '\0')? true : response != valid3)
          && ((valid4 == '\0')? true : response != valid4))
    {
        //print options
        cout << "Please enter only: " << valid1;
        if (valid2 != '\0')
            cout << " or " << valid2;
        if (valid3 != '\0')
            cout << " or " << valid3;
        if (valid4 != '\0')
            cout << " or " << valid4;
        cout << endl;

        cin.get(response);

        if(response != '\n')
        {
            cin.ignore(INT_MAX, '\n');
        }

        if(isalpha(response))
            response = toupper(response);
    }

    cout << endl;

    return response;
}


#endif // RESPONSE_CHECK_H_INCLUDED
