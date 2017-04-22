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
char responseCheck(char val1, char val2, char val3, char val4, char val5)
{
    char response = '\0'; //user input

    //checks user input against given valid characters
    while(response != val1
          && ((val2 == '\0')? true : response != val2)
          && ((val3 == '\0')? true : response != val3)
          && ((val4 == '\0')? true : response != val4)
          && ((val5 == '\0')? true : response != val5))
    {
        //print options
        cout << "Please enter only: " << val1;
        if (val2 != '\0')
            cout << " or " << val2;
        if (val3 != '\0')
            cout << " or " << val3;
        if (val4 != '\0')
            cout << " or " << val4;
        if (val5 != '\0')
            cout << " or " << val5;
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
