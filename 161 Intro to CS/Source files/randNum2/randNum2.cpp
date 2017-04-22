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
#include <cstring>

using namespace std;

int main()
{
    const int SIZE = 11; //max size for arrays
    int maximum, minimum, // max and min for the rand number
        range, // the number of possible rand numbers
        number; // rand number
    char phrase1[SIZE], phrase2[SIZE];
    bool error = false; // did the user put in a number only

	srand(time(0));
    cout << "Please give me a whole number. ";
    cin.getline(phrase1,SIZE);
    do
    {
        if (error)
        {
            cout << "You did not give me a whole number."
                 << "\nPlease give me an integer only." << endl;
            cin.getline(phrase1, SIZE);
            error = false;
        }

        for (int i = 0; i < strlen(phrase1); i++)
        {
            if (!isdigit(phrase1[i]))
				error = true;
        }
    } while (error);

    cout << "What is another number?" << endl;
    cin.getline(phrase2, SIZE);
    do
    {
        if (error)
        {
            cout << "You did not give me a whole number."
                 << "\nPlease give me an integer only." << endl;
            cin.getline(phrase2, SIZE);
            error = false;
        }

        for (int i = 0; i < strlen(phrase2); i++)
        {
            if (!isdigit(phrase2[i]))
                error = true;
        }
    } while (error);

    minimum = atoi(phrase1);
    maximum = atoi(phrase2);

    if (maximum - minimum < 0)
    {
        int temp = minimum; //temporary storage
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
