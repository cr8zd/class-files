/******************************************************************************
* Author: Jennifer Frase
* Date Created: 10/10/14
* Last Modification Date: 10/17/14
* Filename: numGuess.cpp
*
* Overview:
* This program will have one user pick a number between a min
* and max. A second user then has to guess what that number is.
* They have a certain number of guesses and the program will tell
* them if they are too high or too low after each guess. It will
* then adjust the range of numbers to reflect this. All ranges
* are inclusive.
*
* Input:
* The input will be an integer from the first user which will
* be the secret number. A second user inputs integers in the
* given range until they get the secret number or run out of
* guesses. After a game is complete a user can input y to
* play again or n to leave the program.
*
* Caution, wont catch input that is not a number.
*
* Output:
* The output for this program will whether the second users
* numbers are too high, too low, or correct after each guess.
* Before guessing the second user is given a range and how
* many guesses they have left. Once they either get the secret
* number or run out of guesses the program will say congrats or
* reveal the secret number and the users closest guess respectively.
* Once the game is complete the users are asked if they want to
* continue.
*
* PS. If you want to see all output together, lower SCEEN_PUSH
******************************************************************************/

#include <iostream>
#include <string>
#include <cmath>
//#include <cctype>

using namespace std;

int main()
{
	const int MAX = 100; // Maximum possible number
	const int MIN = 0; // Minimum possible number
	const int MAX_GUESSES = 5; // Max number of guesses
	const int SCREEN_PUSH = 50; // Number of lines between player 1's secret
                               // number and player 2's guesses
	double secretInput; // Player 1's input - controls for doubles
	double numInput; // Player 2's input - controls for doubles
	int secretNum; // Player 1's secret number
	int num; // Player 2's guess
	int minimum, maximum; //Min and Max for Player 2's guess
	int guess; // number of guesses left
	int closeNum; // closest guess to the secret number
                  // initialized at 2*(MAX - MIN)
	int closeNum2; // Player two picks the other number with the same
                   // difference from the secret number
                   // initialized at 2*(MAX - MIN)
	bool secondCloseNum; // sets to true if player 2 gets both closest numbers
	char repeat; // store whether user wants to continue

	//repeat program until player says n
	do
	{
		//ask for a secret number
		cout << "What secret number do you want between "
			 << MIN << " and " << MAX << " inclusive?" << endl;
		cin >> secretInput;
		secretNum = secretInput;
		if (abs(secretInput - secretNum) > .0000000001)
            cout << "You gave a non integer, it will be truncated." << endl;

		// input error check for secret number
		while (secretNum > MAX || secretNum < MIN)
		{
			cout << "You cannot pick a number less than 0 or greater"
				 << " than 100." << endl;
			cout << "Please give a new number." << endl;
			cin >> secretInput;
            secretNum = secretInput;
            if (abs(secretInput - secretNum) > .0000000001)
                cout << "You gave a non integer, it will be truncated." << endl;
		}

		/* push the secret number off the screen (hopefully)
		* you can easily increase the number of new lines
		* by adjusting SCREEN_PUSH */
		string space;
		space.assign(SCREEN_PUSH, '\n');
		cout << space;

		//initialize variables inside loop so other runs initialize as well
		minimum = MIN;
		maximum = MAX;
		guess = MAX_GUESSES;
		num = MAX + 1;
		closeNum = 2*(MAX - MIN); // width of range * 2 for safe measure
		closeNum2 = 2*(MAX - MIN);
		secondCloseNum = false;

		// run through the second users guesses until they get the
		// number or run out of guesses
		while (num != secretNum && guess > 0)
		{
			cout << "\nThe range of possible numbers is " << minimum
				 << " to " << maximum << "." << endl;

			if (guess == 1)
				cout << "This is your last guess!" << endl;
			else if (guess > 1)
				cout << "You have " << guess << " guesses left." << endl;
			else // guess is zero or less, so loop didn't preform properly
				cout << "You have an error" << endl;

			cout << "\nWhat do you think the secret number is?" << endl;
			cin >> numInput;
        	num = numInput;
        	if (abs(numInput - num) > .0000000001)
                cout << "You gave a non integer, it will be truncated." << endl;


			// input error check for secret number
			while (num > maximum || num < minimum)
			{
				cout << "You cannot pick a number less than " << minimum
					 << " or greater than " << maximum << "." << endl;
				cout << "Please give a new number." << endl;
				cin >> numInput;
                num = numInput;
                if (abs(numInput - num) > .0000000001)
                    cout << "You gave a non integer, it will be truncated." << endl;
			}

			cout << "Your guess is";

			// determine if the guessed num is too high, too low, or correct
			if (num > secretNum)
			{
				cout << " too high." << endl;
				maximum = num - 1;
			}
			else if (num < secretNum)
			{
				cout << " too low." << endl;
				minimum = num + 1;
			}
			else
			{
				cout << " correct!" << endl;
			}

			//determine if closest guess
			if (abs(num - secretNum) < abs(closeNum - secretNum))
            {
                closeNum = num;
            }
            else if (abs(num - secretNum) == abs(closeNum - secretNum))
            {
                closeNum2 = num;
                secondCloseNum = true;
            }
			guess--;
		}

		if (abs(closeNum2 - secretNum) != abs(closeNum - secretNum))
            secondCloseNum = false;

		if (num != secretNum && guess == 0)
		{
			cout << "\nThe secret number was " << secretNum << "." << endl;
			cout << "Your closest guess";
			if (secondCloseNum)
            {
                cout << "es were " << closeNum << " and " << closeNum2 << "."
                     << endl;
            }
            else
            {
                cout << " was " << closeNum << "." << endl;
            }
		}
		else if (num == secretNum)
		{
			cout << "\nCongratulations you found the secret number!" << endl;
		}
		else
		{
			cout << "You had an error" << endl;
		}

		// Determine if they want to play again
		cout << "\nDo you want to play agian? Y or N" << endl;
		cin >> repeat;
		repeat = tolower(repeat);
		while (repeat != 'y' && repeat != 'n')
		{
			cout << "You can only type either Y for yes or N for no." << endl;
			cout << "Do you want to play again?" << endl;
			cin >> repeat;
			repeat = tolower(repeat);
		}
		cout << endl;

	} while (repeat == 'y');

	return 0; //false; had no errors
}
