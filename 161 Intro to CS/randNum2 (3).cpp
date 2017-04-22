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
#include <string.h>

using namespace std;

int main()
{
    const int SIZE = 11;
    int maximum, minimum, // max and min for the rand number
        range, // the number of possible rand numbers
        number; // rand number
    char input1[SIZE], input2[SIZE];
    bool error = false; // did the user put in a number only

	srand(time(0));
    cout << "Please, a whole number. ";
    cin.getline(input1,SIZE);
    do
    {
        if (error)
        {
            cout << "You did not give me a number."
                 << "\nPlease give me a number only." << endl;
            cin.getline(input1, SIZE);
            error = false;
        }

        for (int i = 0; i < strlen(input1); i++)
        {
            if (!isdigit(input1[i]))
				error = true;
        }
    } while (error);

    cout << "What is another number?" << endl;
    cin.getline(input2, SIZE);
    do
    {
        if (error)
        {
            cout << "You did not give me a number."
                 << "\nPlease give me a number only." << endl;
            cin.getline(input2, SIZE);
            error = false;
        }

        for (int i = 0; i < strlen(input2); i++)
        {
            if (!isdigit(input2[i]))
                error = true;
        }
    } while (error);

    minimum = atoi(input1);
    maximum = atoi(input2);

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
	cin.get();

    return 0;
}
