/******************************************************************************
* Author: Jennifer Frase
* Date Created: 10/17/14
* Last Modification Date: 10/17/14
* Filename: randNum2.cpp
*
* Overview:
* This program will pick a random number between a given
* max and min. Then display that number.
*
* Input:
* The input will be two numbers which represent the max
* and min numbers the random number can choose from.
*
* Output:
* The output for this program will be the random number
******************************************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

int main()
{
    int maximum, minimum, // max and min for the rand number
        range, // the number of possible rand numbers
        number; // rand number
    string input1, input2; // user input
    bool error = false; // did the user put in a number only
    srand(time(0));
    cout << "Please give me a whole number." << endl;
    getline(cin, input1);
    do
    {
        if (error)
        {
            cout << "You did not give me a number."
                 << "\nPlease give me a number only." << endl;
            getline(cin, input1);
            error = false;
        }
        for (int i = 0; i < input1.length(); i++)
        {
            if (!isdigit(input1[i]))
                error = true;
        }
    } while (error);

    cout << "What is another number?" << endl;
    getline(cin, input2);
    do
    {
        if (error)
        {
            cout << "You did not give me a number."
                 << "\nPlease give me a number only." << endl;
            getline(cin, input2);
            error = false;
        }

        for (int i = 0; i < input2.length(); i++)
        {
            if (!isdigit(input2[i]))
                error = true;
        }
    } while (error);

    char userMin[(int)input2.length()], userMax[(int)input1.length()];

    for (int i = 0; i < input2.length(); i++)
    {
        userMin[i] = input2[i];
    }

    for (int i = 0; i < input1.length(); i++)
    {
        userMax[i] = input1[i];
    }

    minimum = atoi(userMin);
    maximum = atoi(userMax);

    if (maximum - minimum < 0)
    {
        int temp = minimum;
        minimum = maximum;
        maximum = temp;
    }

    range = maximum - minimum + 1;

    number = rand() % range + minimum;

    cout << "\nThe random number generated between "
         << maximum << " and " << minimum
         << "\nis: " << number << endl;

    return 0;
}
