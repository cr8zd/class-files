/******************************************************************************
* Author: Jennifer Frase
* Date Created: 10/22/14
* Last Modification Date: 10/22/14
* Filename: mpg.cpp
*
* Overview:
* This program will calculate the mpg of a car trip given a number of liters
* used and miles traveled.
*
* Input:
* The input will be double numbers, the first for liters used and the second
* for miles traveled.
*
* Output:
* The output for this program will be mpg of the trip.
******************************************************************************/

#include <iostream>
#include <iomanip>

using namespace std;

//gets a valid number from user
double NumCheck();

//calculates and prints the mpg of a car trip
void MPG(double miles, double liters);

const double GPL = 0.264179; //gallons per liter conversion constant

int main()
{
    double liters; //user input for liters used
    double miles; //user input for miles traveled
    char response; //user input of calculate again

    do
    {
        response = NULL;
        cout << "How many liters did your car use? ";
        liters = NumCheck();
        cout << endl;
        cout << "\nHow many miles did you travel? ";
        miles = NumCheck();
        cout << endl;
        MPG(miles, liters);
        cout << "\nDo you want to run another calculation?" << endl;

        //gets response and only accepts a y or an n
        while(response != 'Y' && response != 'N')
        {
            cout << "Please give only Y or N." << endl;
            if (cin.peek() == '\n')
                cin.ignore();
            response = cin.get();
            response = toupper(response);
        }

        cout << endl;
    }while (response == 'Y');

    return 0;
}

/******************************************************************************
* Entry: liters is the number of liters used to travel given miles
*
* Exit: calculates the number of gallons used in the given liters and then
* calculates the miles per gallon for the trip. Prints out the results.
*
* Purpose: calculating the printing the miles per gallon of a car trip
*
******************************************************************************/
void MPG(double miles, double liters)
{
    const double ZERO = .0000001; //zero used for doubles
    double mpg; //miles per gallon
    double gallons; //gallons used

    gallons = liters * GPL;
    cout << setprecision(2) << fixed;

    if (gallons < ZERO)
    {
        if (miles < ZERO)
        {
            cout << "You didn't travel so your mpg is 0." << endl;
        }
        else
        {
            cout << "You used 0 gallons and have infinite mpg." << endl;
        }
    }
    else
    {
        mpg = miles / gallons;
        cout << "You used " << gallons << " gallon" << (gallons == 1? "." : "s")
             << " and had an mpg of " << mpg << "." << endl;
    }

    if (mpg < ZERO)
         cout << "\nGET A NEW CAR!" << endl;
}

/******************************************************************************
* Entry: none
*
* Exit: gets user input and checks that it is a number, returns input if it is
*
* Purpose: getting and checking validity of input
*
******************************************************************************/
double NumCheck()
{
    double number; //user input
    string junk; //throws input away if not a number
    bool error = false; //input was not a number

    //loops while input is not a number
    do
    {
        cin >> number;

        if (cin.fail())
        {
            cout << "Give only numbers please." << endl;
            cin.clear();
            getline(cin, junk);
            error = true;
        }
        else
        {
            error = false;
        }

    } while (error);

    return number;
}
