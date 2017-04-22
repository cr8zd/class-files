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
* Entry: char values for which the function can check against
*
* Exit: gets user input and compares it to the valid responses until it finally
*       gets a valid response
*
* Purpose: checking that a response is valid
*
******************************************************************************/
char responseCheck(char val1, char val2, char val3, char val4, char val5);

char responseCheck(char val1, char val2, char val3, char val4);

char responseCheck(char val1, char val2, char val3);

char responseCheck(char val1, char val2);



#endif // RESPONSE_CHECK_H_INCLUDED
