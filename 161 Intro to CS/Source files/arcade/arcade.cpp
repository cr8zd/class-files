/******************************************************************************
* Author: Jennifer Frase
* Date Created: 10/10/14
* Last Modification Date: 10/10/14
* Filename: arcade.cpp
*
* Overview:
* This program will determine how many candy bars and gum
* balls you can get with a given number of coupons when you
* prefer candy bars over gum balls.
*
* Input:
* The input will be an integer from the user that will
* represent the number of coupons available.
*
* Output:
* The output for this program will be how many candy bars
* you can get with the coupons, then how many gum balls you
* can get with the remaining coupons.
******************************************************************************/

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	const int BAR_RATE = 10; // exchange rate for candy bars
	const int GUM_RATE = 3; // exchange rate for gum balls
	double userInput; // control in case a double is given
    double remainder; // variable to determine if double is given
	int coupons; // user input for the amount of coupons available
	int bars; // how many candy bars you can get
	int gum; // how many gum balls you can get

	// ask how many coupons there are
	cout << "How many coupons do you have?" << endl;
	cin >> userInput;
	coupons = userInput;
	remainder = userInput - coupons;

    // check that coupons is positive numbers and user input a whole number
	while (userInput < 0 || abs(remainder) > .0000000001)
	{
	    char response;

	    // asks if they meant to give a partial number
	    if (abs(remainder) > .0000000001)
		{
		    cout << "You cannot turn in partial coupons, and you gave:\n"
		         << userInput << ", a partial number for a coupon."
                 << "\nDo you want this number truncated? Y or N:" << endl;
            cin >> response;
            if (tolower(response) == 'n')
            {
                cout << "Then please give a new number." << endl;
                cin >> userInput;
                coupons = userInput;
                remainder = userInput - coupons;
            }
            else if (tolower(response) == 'y')
            {
                cout << endl;
                userInput = coupons;
                remainder = userInput - coupons;
            }
            else
            {
                cout << "You did not say y or n, so it will be truncated."
                     << endl;
                userInput = coupons;
                remainder = userInput - coupons;
            }
		}

		// asks if they meant to give a negative number
		if (userInput < 0)
        {
            cout << "\nYou cannot have negative coupons."
			 << "\nDid you mean the positive of " << userInput << "? Y or N"
			 << endl;
            cin >> response;
            if (tolower(response) == 'n')
            {
                cout << "Then please give a new number greater than or"
                     << " equal to zero." << endl;
                cin >> userInput;
                coupons = userInput;
                remainder = userInput - coupons;
            }
            else if (tolower(response) == 'y')
            {
                cout << endl;
                userInput = -userInput;
                coupons = -coupons;
            }
            else
            {
                cout << "You did not say y or n, so it will be assumed y."
                     << endl;
                userInput = -userInput;
                coupons = -coupons;
            }
        }
	}

	// initialize and calculate bars and gum
	bars = coupons / BAR_RATE;
	gum = (coupons % BAR_RATE) / GUM_RATE;

	// Print how many bars and gum you can get
	cout << "\nWith " << coupons << " coupon" << (coupons == 1? "" : "s")
         << " you can get:" << endl;
    cout << bars << " candy bar" << (bars == 1? "" : "s") << endl;
	cout << gum << " gum ball" << (gum == 1? "" : "s") << endl;

	return 0; //false; had no errors
}
