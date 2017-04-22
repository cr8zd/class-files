/******************************************************************************
* Author: Jennifer Frase
* Date Created: 11/24/14
* Last Modification Date: 11/26/14
* Filename: carLot2.cpp
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
#include <stdexcept>
#include <cmath>
#include <new>

using namespace std;

//a date in time
class Date
{
    private:
        int day, //date's day
            month, //date's month
            year; //date's year
    public:
        Date(){};

        Date(int , int , int );

        int getDay() const //return day
        { return day; }

        int getMonth() const //return month
        { return month; }

        int getYear() const //return year
        { return year; }
};

//storage for a car's information
class Car
{
    private:
        string make, //car's make
               model; //car's model
        int year; //year car was made
        Date datePurchased, //date lot owner purchased car
             dateSold; //date lot owner sold car
        double purchasePrice, //purchase price by lot owner
               salePrice; //sale price by lot owner
        bool isSold; //whether the car is still lot owner's

    public:
        Car (){};

        Car(string, string, int, Date, double, bool, Date, double);

        Car(string, string, int, Date, double, bool);

        string getMake() const //return make
        { return make; }

        string getModel() const //return model
        { return model; }

        int getYear() const //return year
        { return year; }

        Date getPurDate() const //return datePurchased
        { return datePurchased; }

        Date getSaleDate() const //return dateSold
        { return dateSold; }

        double getPurPrice() const //return purchasePrice
        { return purchasePrice; }

        bool getIsSold() const //return isSold
        { return isSold; }

        double getProfit() const //return profit
        { return (isSold? salePrice - purchasePrice : NAN); }
};

class CarLot
{
    private:
        vector<Car> lot; //storage for Car information

    public:
        void addCar(Car veh) //add passed in Car to vector
        { lot.push_back(veh); }
        void listCurrentInv() const;
        double getMonthProfit(int, int) const;
};

/******************************************************************************
* Entry: There are three int parameters, the day, month, and year for the Date
*
* Exit: Checks that the month is valid and the day is valid for that month,
*       before adding to the Date
*
* Purpose: initializing the Date
******************************************************************************/
Date::Date(int d, int m, int y)
{
    int maxDay; //last day of user input month

    //Get last day of given month
    if(m == 2)
    {
        maxDay = 28;
    }
    else
    {
        if(m % 2 == 1)
            maxDay = (m > 7? 30 : 31);
        else
            maxDay = (m > 7? 31 : 30);
    }

    if(d < 1 || d > maxDay || m > 12 || m < 1)
        throw std::invalid_argument("ERROR: The given month and day are not a valid date.");

    year = y;
    month = m;
    day = d;
}

/******************************************************************************
* Entry: There are eight parameters, the first two are string for the make
*        and model of the cars, the third is an int for the year of the car,
*        the fourth and seventh are Dates corresponding the to purchase and
*        sale dates, the fifth and eighth are the cost of purchase and the
*        sale price, and the sixth is whether the car is sold - should be true.
*
* Exit: Initializes the member variables with the given parameters
*
* Purpose: initializing the sold Car
******************************************************************************/
Car::Car(string mak, string mod, int y, Date purDate, double purPrice, bool sold, Date saleDate, double salePr)
{
    make = mak;
    model = mod;
    year = y;
    datePurchased = purDate;
    purchasePrice = purPrice;
    isSold = sold;
    dateSold = saleDate;
    salePrice = salePr;
}

/******************************************************************************
* Entry: There are six parameters, the first two are string for the make
*        and model of the cars, the third is an int for the year of the car,
*        the fourth is a Date corresponding the to purchase date, the fifth is
*        the cost of purchase, and the sixth is whether the car is sold -
*        should be false.
*
* Exit: Initializes the member variables with the given parameters
*
* Purpose: initializing the unsold Car
******************************************************************************/
Car::Car(string mak, string mod, int y, Date purDate, double purPrice, bool sold)
{
    make = mak;
    model = mod;
    year = y;
    datePurchased = purDate;
    purchasePrice = purPrice;
    isSold = sold;
}

/******************************************************************************
* Entry: none
*
* Exit: Loops through all the cars and displays all the information on the
*       cars that have not been sold.
*
* Purpose: Printing current inventory
******************************************************************************/
void CarLot::listCurrentInv() const
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
        if (!lot[i].getIsSold())
        {
            cout << left << setw(15) << lot[i].getMake();

            cout << setw(21) << lot[i].getModel();

            cout << setw(0) << (lot[i].getPurDate().getYear() / 10 == 0? "0" : "")
                 << (lot[i].getYear() / 100 == 0? "0" : "")
                 << (lot[i].getYear() / 1000 == 0? "0" : "") << lot[i].getYear()
                 << setw(6) << "";

            cout << setw(0) << (lot[i].getPurDate().getMonth() / 10 == 0? "0" : "")
                 << lot[i].getPurDate().getMonth() << "/";

            cout << (lot[i].getPurDate().getDay() / 10 == 0? "0" : "")
                 << lot[i].getPurDate().getDay() << "/";

            cout << (lot[i].getPurDate().getYear() / 10 == 0? "0" : "")
                 << (lot[i].getPurDate().getYear() / 100 == 0? "0" : "")
                 << (lot[i].getPurDate().getYear() / 1000 == 0? "0" : "")
                 << lot[i].getPurDate().getYear();

            cout << left << fixed << showpoint << setprecision(2) << setw(6) << ""
                 << right << setw(11) << lot[i].getPurPrice() << endl;

            cout << line << endl;
            carsOnLot++;
        }
    }
    cout << "\nTOTAL CARS ON LOT: " << carsOnLot << endl;
}

/******************************************************************************
* Entry: There are two int parameters, a month and year
*
* Exit: Checks if a car is sold on the given month and year and if it is, gets
*       that car's profit, adding it to the total profit for the month. Returns
*       the total profit for the given month of the given year
*
* Purpose: getting the profit for a specific month
******************************************************************************/
double CarLot::getMonthProfit(int month, int year) const
{
    double total = 0; //total for the month

    for (int i = 0; i < lot.size(); i++)
    {
        if(lot[i].getIsSold())
        {
            if(lot[i].getSaleDate().getYear() == year
               && lot[i].getSaleDate().getMonth() == month)
            {
                total += lot[i].getProfit();
            }
        }
    }

    return total;
}

//gets and checks that user response is valid
char responseCheck(char, char, char, char);

//gets the information for a Car
Car makeCar();

int main()
{
    const int SCREEN_PUSH = 25; //print the number of lines to clear screen
    string space; //used to push the output off screen
    CarLot lot; //storage for the Cars
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
        {
            lot.addCar(makeCar());
            cin.get();
        }
        else if (response == '2') //list inventory
        {
            lot.listCurrentInv();
        }
        else if (response == '3') //get profit for given month
        {
            int month, year;
            cout << "What year do you want to check for a profit? ";
            cin >> year;
            cout << "\nWhat month of that year?";
            cin >> month;
            cout << fixed << showpoint << setprecision(2) << endl;
            cout << "TOTAL PROFIT FOR " << (month / 10 == 0? "0" : "")
                 << month << "/" << (year / 1000 == 0? "0" : "")
                 << (year / 100 == 0? "0" : "") << (year / 10 == 0? "0" : "")
                 << year << ": $" << lot.getMonthProfit(month, year) << endl;
            cin.get();
        }

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
* Entry: None
*
* Exit: Gets user inputs for all the information of the car before creating a
*       new Car.
*
* Purpose: Creating a new Car.
******************************************************************************/
Car makeCar()
{
    //Car information
    char sold; //Y if car is sold, N if car is not
    string  make,
            model;
    int yearMade;
    double purPrice,
           salePrice;
    int yearP, yearS, monthP, monthS, dayP, dayS;

    cout << "What is the make of the car?" << endl;
    while(isspace(cin.peek()))
    {
        cin.ignore();
    }
    getline(cin, make);

    cout << "\nWhat is the model name of the car?" << endl;
    while(isspace(cin.peek()))
    {
        cin.ignore();
    }
    getline(cin, model);

    cout << "\nWhat is the year of the car?" << endl;
    cin >> yearMade;

    cout << "\nWhat was the purchase date of the car?" << endl;
    cout << "What year? ";
    cin >> yearP;

    cout << "What month? ";
    cin >> monthP;

    cout << "What day? ";
    cin >> dayP;

    Date purDate(dayP, monthP, yearP);

    cout << "\nWhat was the purchase price of the car?" << endl;
    cin >> purPrice;

    cout << "\nIs the car sold?" << endl;
    cin >> sold;

    if(toupper(sold) == 'Y')
    {
        cout << "\nWhat was the sale date of the car?" << endl;
        cout << "What year? ";
        cin >> yearS;

        cout << "What month? ";
        cin >> monthS;

        cout << "What day? ";
        cin >> dayS;

        Date saleDate(dayS, monthS, yearS);

        cout << "\nWhat was the sale price of the car?" << endl;
        cin >> salePrice;

        Car veh(make, model, yearMade, purDate, purPrice, true, saleDate, salePrice);
        return veh;
    }
    else
    {
       Car veh(make, model, yearMade, purDate, purPrice, false);
       return veh;
    }
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

