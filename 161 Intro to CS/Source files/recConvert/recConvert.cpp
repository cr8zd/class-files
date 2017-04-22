/******************************************************************************
* Author: Jennifer Frase
* Date Created: 10/27/14
* Last Modification Date: 10/30/14
* Filename: recConvert.cpp
*
* Overview:
* This program will convert between decimal and binary numbers.
*
* Input:
* The input will be either a decimal number or a binary number stored as
* int or string respectively.
*
* Output:
* The output for this program will be a binary number or a decimal number
* if the user input a decimal number or binary number respectively.
******************************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>
#include <climits>

using namespace std;

//converts binary numbers to decimal numbers
int bin2Num(string binStr, int i);

//converts decimal numbers to binary numbers
string num2Bin(int &num, int i);

//checks that user input was valid based on the type of conversion
int isValid(string response, char convResp);

//checks that a response is valid for up to 3 valid inputs
char responseCheck(char valid1, char valid2, char valid3);

int main()
{
    const int START_VALUE = 1; //value that recursion starts at
    char response = '1'; //response to menu initialized to enter while loop
    string numGiven; //number in either binary or decimal given
    int validResp; //0 for valid input
    int number; //numGiven in int for decimal numbers

    //continue until user chooses to exit
    while (response != '3')
    {
        cout << "Do you want to:"
             << "\n1) convert binary into decimal"
             << "\n2) convert decimal into binary"
             << "\n3) exit the program" << endl;
        response = responseCheck('1', '2', '3');

        //user didn't choose exit
        if (response != '3')
        {
            cout << "\nPlease give me a positive "
                 << (response == '1'? "binary" : "decimal")
                 << " number." << endl;

            getline(cin, numGiven);
            validResp = isValid(numGiven, response);
            number = atoi(numGiven.c_str());

            //user input a valid number so convert and print
            if (validResp == 0)
            {
                if (response == '1')
                    cout << "\nYour number in decimal notation is "
                         << bin2Num(numGiven, START_VALUE) << ".\n" << endl;
                else
                    cout << "\nYour number in binary is "
                         << num2Bin(number, START_VALUE)
                         << ".\n" << endl;
            }
        }
    }
    return 0;
}

/******************************************************************************
* Entry: one string variable, binStr, that is the binary number the user input
* and an integer which is the representative value of each position in a
* binary number ie the first 0/1 is 1, the second is 2, the third is 4
*
* Exit: looks at the last char in binStr, if it is a 1 then it adds i to the
* returned value, then is erases that char before repeating until the string
* is empty. Returns the binary version of the decimal number.
*
* Purpose: converting a binary number into decimal
******************************************************************************/
int bin2Num(string binStr, int i)
{
    char number;//current character in binStr
    int value = 0; //returned value for the binary number

    number = binStr.at(binStr.length() - 1);

    if (number == '1')
        value += i;

    binStr.erase(binStr.end() - 1);

    //there is still another binary part to get
    if (!binStr.empty())
        value += bin2Num(binStr, i * 2);

    return value;
}

/******************************************************************************
* Entry: two int variables where the first is a reference to the number the
* user input and the second is the representative value of each position in a
* binary number ie the first 0/1 is 1, the second is 2, the third is 4
*
* Exit: takes num and goes to the highest representative value in a binary
* number that is not higher than num and adds a 1 or 0 to a string for every
* position at or below that value depending on if that value is still in num
* where if it is the value is subtracted from num. Returns the decimal
* version of the binary number.
*
* Purpose: converting a decimal number into binary
******************************************************************************/
string num2Bin (int &num, int i)
{
    string binaryNum; //returned string

    //advance to next highest binary number value if
    //num is higher than 2 * i
    if ((num / (2 * i)) >= 1)
    {
        binaryNum = num2Bin(num, i * 2);
    }

    //if current binary is in num add 1 to string and subtract from num
    //else add 0 to string
    if (num / i >= 1)
    {
        binaryNum += '1';
        num -= i;
    }
    else
    {
        binaryNum += '0';
    }

    return binaryNum;
}

/******************************************************************************
* Entry: One string variable that represents the users input for a binary or
* decimal prompt, and one char variable the represents which they chose
*
* Exit: takes each character in response and makes sure it is an number, and
* if convResp was '1' then makes sure that each number is either a 1 or 0
*
* Purpose: checking that a response is valid depending on which option they
* chose
******************************************************************************/
int isValid(string response, char convResp)
{
    //check each character in response that it is a number
    for(int i = 0; i < response.length(); i++)
    {
        if (!isdigit(response[i]))
        {
            cout << "\nYou did not give me a valid number.\n" << endl;
            return 1;
        }

        //if converting from a binary check that each character is either
        //a 1 or 0
        if (convResp == '1')
        {
            if(response[i] != '1' && response[i] != '0')
            {
                cout << "\nYou did not give me a valid binary number.\n"
                     << endl;
                return 1;
            }
        }
    }
    return 0;
}

/******************************************************************************
* Entry: Three char values for which the function can check against, can be
*        '\0'
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
