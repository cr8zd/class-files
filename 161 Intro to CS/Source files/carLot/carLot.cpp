/******************************************************************************
* Author: Jennifer Frase
* Date Created: 11/19/14
* Last Modification Date: 11/22/14
* Filename: carLot.cpp
*
* Overview:
* This program will allow the user to create a car lot inventory where they can
* add a car, see the contents of the lot, and get the total profit for all cars
* sold in a given month.
*
* Input:
* The input will be a range of information on the cars added to the inventory,
* such as the car's make or the purchase price or if the car has been sold.
* This is in addition to picking a number from the menu on what the user wants
* to do in the program.
*
* Output:
* The output for this program can be a list of all cars still on the lot and/or
* the profits from a given month of a given year, as well as any prompts.
******************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <climits>

using namespace std;

//a date in time
struct Date
{
    int day, //date's day
        month, //date's month
        year; //date's year
};

//storage for a car's information
struct Car
{
    string make, //car's make
           model; //car's model
    int year; //year car was made
    Date datePurchased, //date lot owner purchased car
         dateSold; //date lot owner sold car
    double purchasePrice, //purchase price by lot owner
           salePrice; //sale price by lot owner
    bool isSold; //whether the car is still lot owner's
};

//gets and checks that user response is valid
char responseCheck(char, char, char, char);

//gets the information for a Date
void getDate(Date &);

//adds a Car with all the information to the vector
void addCar(vector<Car> &);

//lists all unsold cars in the vector
void listCars(const vector<Car> &);

//calculates the profit of cars sold on a given month
void printProfit(const vector<Car> &);

int main()
{
    const int SCREEN_PUSH = 25; //print the number of lines to clear screen
    string space; //used to push the output off screen
    vector<Car> lot; //storage for the Cars
    char response; //user response to menu

    space.assign(SCREEN_PUSH, '\n');

    cout << "Car Inventory:" << endl;

    //get user commands until they want to quit
    do
    {
        cout << "\nWhat do you want to do?\n"
             << "1) add a car\n"
             << "2) list cars on lot\n"
             << "3) get profit for a given month\n"
             << "4) quit" << endl;
        response = responseCheck('1', '2', '3', '4');

        cout << space;

        if (response == '1') //add car
            addCar(lot);
        else if (response == '2') //list inventory
            listCars(lot);
        else if (response == '3') //get profit for given month
            printProfit(lot);

        if (response != '4')
        {
            cout << "\nHit ENTER to go back." << endl;
            cin.get();
            cout << space;
        }

    }while (response != '4');

    return 0;
}

/******************************************************************************
* Entry: There is one parameter, a vector of Cars
*
* Exit: Gets a given month of a given year and loops through all the Cars.
*       If a car has been sold on the given specific month then adds the
*       purchase price to purchase total and sale price to sale total. After
*       looping prints the profit for that month.
*
* Purpose: getting the profit for a specific month
******************************************************************************/
void printProfit(const vector<Car> &lot)
{
    int year, month; //user input for year and month to check
    double saleTotal = 0.00; //total sale prices for specified month
    double purchaseTotal = 0.00; //total purchase prices for cars sold in
                                 //specified month

    cout << "What year do you want to check?" << endl;
    cin >> year;

    cout << "What month of that year do you want to check?" << endl;
    do
    {
        cin >> month;
        if (month < 1 || month > 12)
          cout << "Please give a month between 1 and 12." << endl;
    }while (month < 1 || month > 12);

    //get saleTotal and purchaseTotal prices
    for (int i = 0; i < lot.size(); i++)
    {
        if(lot[i].isSold)
        {
            if(lot[i].dateSold.year == year && lot[i].dateSold.month == month)
            {
                saleTotal += lot[i].salePrice;
                purchaseTotal += lot[i].purchasePrice;
            }
        }
    }

    cout << fixed << showpoint << setprecision(2) << endl;
    cout << "TOTAL PROFIT FOR " << month << "/" << year << ": $"
         << saleTotal - purchaseTotal << endl;
    cin.get();
}

/******************************************************************************
* Entry: There is one parameter, a vector of Cars
*
* Exit: Loops through all the cars and desplays all the information on the
*       cars that have not been sold.
*
* Purpose: Printing current inventory
******************************************************************************/
void listCars(const vector<Car> &lot)
{
    int carsOnLot = 0; //number of cars not sold
    string line; //used to print a line above and below cars

    line.assign(79, '-');

    cout << "MAKE           MODEL                YEAR    PUR. DATE M/D/Y"
         << "    PUR. PRICE ($)\n" << endl;
    cout << line << endl;

    //print items in lot
    for(int i = 0; i < lot.size(); i++)
    {
        if (!lot[i].isSold)
        {
            cout << left << setw(15) << lot[i].make;
            cout << setw(21) << lot[i].model;
            cout << setw(0) << (lot[i].year / 100 == 0? "0" : "")
                 << (lot[i].year / 1000 == 0? "0" : "") << lot[i].year
                 << setw(6) << "";
            cout << setw(0) << (lot[i].datePurchased.month / 10 == 0? "0" : "")
                 << lot[i].datePurchased.month << "/";
            cout << (lot[i].datePurchased.day / 10 == 0? "0" : "")
                 << lot[i].datePurchased.day << "/";
            cout << (lot[i].datePurchased.year / 100 == 0? "0" : "")
                 << (lot[i].datePurchased.year / 1000 == 0? "0" : "")
                 << lot[i].datePurchased.year;
            cout << left << fixed << showpoint << setprecision(2) << setw(6) << ""
                 << right << setw(11) << lot[i].purchasePrice << endl;
            cout << line << endl;
            carsOnLot++;
        }
    }
    cout << "\nTOTAL CARS ON LOT: " << carsOnLot << endl;
}

/******************************************************************************
* Entry: There is one parameter, a vector of Cars
*
* Exit: Creates a new Car and the user inputs all the information of the car.
*       Afterward the car is added to the vector.
*
* Purpose: Adding a new Car to the vector.
******************************************************************************/
void addCar(vector<Car> &lot)
{
    char sold; //Y if car is sold, N if car is not
    Car object; //storage for car's information

    cout << "What is the make of the car?" << endl;
    while(isspace(cin.peek()))
    {
        cin.ignore();
    }
    getline(cin, object.make);

    cout << "\nWhat is the model name of the car?" << endl;
    while(isspace(cin.peek()))
    {
        cin.ignore();
    }
    getline(cin, object.model);

    cout << "\nWhat is the year of the car?" << endl;
    cin >> object.year;

    cout << "\nWhat was the purchase date of the car?" << endl;
    getDate(object.datePurchased);

    cout << "\nWhat was the purchase price of the car?" << endl;
    cin >> object.purchasePrice;

    cout << "\nIs the car sold?" << endl;
    sold = responseCheck('Y', 'N', '\0', '\0');

    if(sold == 'Y')
    {
        object.isSold = true;

        cout << "\nWhat was the sale date of the car?" << endl;
        getDate(object.dateSold);

        cout << "\nWhat was the sale price of the car?" << endl;
        cin >> object.salePrice;
    }
    else
    {
        object.isSold = false;
    }

    lot.push_back(object);
}

/******************************************************************************
* Entry: There is one parameter, a Date.
*
* Exit: Fills in the information of the Date parameter with user input, making
*       sure a valid day and month are input.
*
* Purpose: Getting a Date's information
******************************************************************************/
void getDate(Date &givenDate)
{
    int maxDay; //last day of user input month

    cout << "What year? ";
    cin >> givenDate.year;

    cout << "What month? ";
    do
    {
        cin >> givenDate.month;
        if (givenDate.month < 1 || givenDate.month > 12)
          cout << "Please give a month between 1 and 12. ";
    }while (givenDate.month < 1 || givenDate.month > 12);


    cout << "What day? ";

    //Get last day of given month
    if(givenDate.month == 2)
    {
        maxDay = 28;
    }
    else
    {
        if(givenDate.month % 2 == 1)
            maxDay = (givenDate.month > 7? 30 : 31);
        else
            maxDay = (givenDate.month > 7? 31 : 30);
    }

    //get valid day for the given month
    do
    {
        cin >> givenDate.day;
        if(givenDate.day < 1 || givenDate.day > maxDay)
         cout << "Please give a day between 1 and " << maxDay << ". ";
    }while (givenDate.day < 1 || givenDate.day > maxDay);
}

/******************************************************************************
* Entry: Four char values for which the function can check against, can be
*        '\0' for all but first
*
* Exit: gets user input and compares it to the valid responses until it final
*       gets a valid response
*
* Purpose: checking that a response is valid
*
******************************************************************************/
char responseCheck(char valid1, char valid2, char valid3, char valid4)
{
    char response = '\0'; //user input

    //checks user input against given valid characters
    while(response != valid1 && ((valid2 == '\0')? true : response != valid2)
            && ((valid3 == '\0')? true : response != valid3)
            && ((valid4 == '\0')? true : response != valid4))
    {
        //print options
        cout << "Please enter only: " << valid1;
        if (valid2 != '\0')
            cout << " or " << valid2;
        if (valid3 != '\0')
            cout << " or " << valid3;
        if (valid4 != '\0')
            cout << " or " << valid4;
        cout << endl;

        if(cin.peek() == '\n')
            cin.ignore();

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

