/******************************************************************************
* Author: Jennifer Frase
* Date Created: 10/22/14
* Last Modification Date: 10/22/14
* Filename: size.cpp
*
* Overview:
* This program will calculate the hat size, shirt size, and pant size of a
* person given their height weight and age.
*
* Input:
* The input will be double numbers, the first for their age, the second for
* their weight, and the third for their height.
*
* Output:
* The output for this program will be their hat size, shirt size, and pant
* size.
******************************************************************************/

#include <iostream>
#include <iomanip>

using namespace std;

//calculates hat size based on weight and height
double HatSizeCalc(double weight, double height);

//calculates shirt size based on weight, height, and age
double shirtSizeCalc(double weight, double height, int age);

//calculates pant size based on weight and age
double PantSizeCalc(double weight, int age);

//gets a valid number from user
double NumCheck();

int main()
{
    const double ZERO = .0000001; //zero for doubles
    int age; //users input for age
    double weight; //user input for weight
    double height; //user input for height
    double hatSize; //calculated hat size
    double shirtSize; //calculated shirt size
    double pantsSize; //calculated pant size
    char response; //user input of calculate again

    //loop while user want to do calculations
    do
    {
        response = '\0';

        cout << "How old are you? ";
        age = NumCheck();
        cout << endl;

        cout << "\nHow many pounds do you weigh? ";
        weight = NumCheck();
        cout << endl;

        //check person doesn't weigh 0 or less pounds
        while (weight <= ZERO)
        {
            cout << "You can not weigh 0 pound or less."
                 << "\nPlease give me a different number.";
            weight = NumCheck();
        }

        cout << "\nHow tall are you in inches? ";
        height = NumCheck();
        cout << endl;

        //check person doesn't weigh 0 or less pounds
        while (height <= 0)
        {
            cout << "You can be 0 inches or less."
                 << "\nPlease give me a different number.";
            height = NumCheck();
        }

        hatSize = HatSizeCalc(weight, height);
        shirtSize = shirtSizeCalc(weight, height, age);
        pantsSize = PantSizeCalc(weight, age);

        cout << "\nYour hat size, shirt size, and pant size are:\n"
             << setprecision(2) << fixed << hatSize << ", "
             << shirtSize << ", and " << pantsSize << endl;

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
* Entry: two doubles: a persons weight and height
*
* Exit: calculates hat size based on weight and height and some conversion
* constants, returns hat size
*
* Purpose: getting a persons hat size
*
******************************************************************************/
double HatSizeCalc(double weight, double height)
{
    const double hatSizeConv = 2.9;
    double hatSize;

    hatSize = (weight/height) * hatSizeConv;

    return hatSize;
}

/******************************************************************************
* Entry: three doubles: a persons weight, height, and age
*
* Exit: calculates shirt size based on given values and some conversion
* constants, returns shirt size
*
* Purpose: getting a persons shirt size
*
******************************************************************************/
double shirtSizeCalc(double weight, double height, int age)
{
    const int weightFactor = 288;
    const double ageFactor = .125;
    const int years = 10;
    const int firstYear = 40;
    double shirtSize;

    shirtSize = height * weight / weightFactor;

    //every 10years starting at 40 add .125 to shirt size
    for (int i = firstYear; i <= age; i += years)
    {
        shirtSize += ageFactor;
    }

    return shirtSize;
}

/******************************************************************************
* Entry: two doubles: a persons weight and age
*
* Exit: calculates pant size based on weight and age and some conversion
* constants, returns pant size
*
* Purpose: getting a persons pant size
*
******************************************************************************/
double PantSizeCalc(double weight, int age)
{
    const double weightFactor = 5.7;
    const double ageFactor = .1;
    const int years = 2;
    const int firstYear = 30;
    double pantSize;

    pantSize = weight / weightFactor;

    //for every 2years starting at age 30 add .1 to pant size
    for(int i = firstYear; i <= age; i += years)
    {
        pantSize += ageFactor;
    }

    return pantSize;
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
