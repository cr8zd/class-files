/******************************************************************************
* Author: Jennifer Frase
* Date Created: 11/17/14
* Last Modification Date: 11/22/14
* Filename: shopCart2.cpp
*
* Overview:
* This program will allow the user to create a shopping cart where they can
* add an item, see the contents of the cart, and get the total for all items
* in the cart.
*
* Input:
* The input will be a number which represents the option the user wants to
* choose which is listed in the menu during the program, as well as the
* name (string), price (double), and quantity (int) for all items the user
* adds to the cart.
*
* Output:
* The output for this program can be a list of the contents of the cart
* and/or the total for all items in the cart as well as any prompts.
******************************************************************************/

#include <iostream>
#include <string>
#include <cstdlib>
//#include <cstdio>
#include <climits>
#include <iomanip>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::fixed;
using std::showpoint;
using std::setprecision;
using std::left;
using std::right;
using std::setw;
using std::atof;


//cart item
class Item
{
    private:
        string name; //name of item
        double price; //price of the item
        int quantity; //number of item in cart

    public:
        //initialize Item with given parameters
        Item(string n, double pr, int qt)
        { name = n;
          price = pr;
          quantity = qt;
        }

        string getName() const //return name
        { return name; }

        double getPrice() const //return price
        { return price; }

        int getAmount() const //return quantity
        { return quantity; }
};

class ShoppingCart
{
    private:
        vector<Item> cart; //storage for Items

    public:
        void addItem(Item obj) //add an Item
        { cart.push_back(obj); }

        void listItems() const;

        void totalPrice() const;
};

/******************************************************************************
* Entry: None
*
* Exit: Lists all added Items' details.
*
* Purpose: displaying what is in the cart
******************************************************************************/
void ShoppingCart::listItems() const
{
    cout << "ITEM                   PRICE ($)     QUANTITY" << endl;

    //print items in cart
    for(int i = 0; i < cart.size(); i++)
    {
        cout << fixed << showpoint << setprecision(2) ;
        cout << left << setw(20) << cart[i].getName();
        cout << right << setw(10) << cart[i].getPrice();
        cout << setw(12) << cart[i].getAmount() << endl;
    }

    cout << endl;
}

/******************************************************************************
* Entry: None
*
* Exit: loops through all Items and calculates the cost
*
* Purpose: getting the total cost of all Items in the cart
******************************************************************************/
void ShoppingCart::totalPrice() const
{
    double total = 0; //total cost

    for (int i = 0; i < cart.size(); i++)
    {
        total += (cart[i].getPrice() * cart[i].getAmount());
    }

    cout << fixed << showpoint << setprecision(2) << endl;
    cout << "TOTAL: $" << total << endl;
}

Item makeItem();

//gets and checks user response against parameters
char responseCheck(char, char, char, char);

//gets and checks that user input is an int
int intCheck(int, int);

//gets and checks that user input is an double
double doubleCheck(double, double, int);

int main()
{
    const int MAX_SIZE = 100; //maximum number of items in cart
    const int SCREEN_PUSH = 25; //print the number of lines to clear screen
    char response; //user input
    string space; // used to push output off the screen
    ShoppingCart cart;

    space.assign(SCREEN_PUSH, '\n');

    cout << "Your shopping cart:" << endl;

    //get user commands until they want to quit
    do
    {
        cout << "\nWhat do you want to do?\n"
             << "1) add an item\n"
             << "2) show cart\n"
             << "3) get total\n"
             << "4) quit" << endl;
        response = responseCheck('1', '2', '3', '4');

        cout << space;

        if (response == '1') //add item
            cart.addItem(makeItem());
        else if (response == '2') //list cart
            cart.listItems();
        else if (response == '3') //print total
            cart.totalPrice();

        //wait till user wants to return to menu then push output off screen
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
* Entry: There are two parameters, the first is an array of Item, and the
*        second is the number of Items in the array
*
* Exit: Creates and adds an Item to the passed array at the next position in
*       said array, getting Item's contents from the user.
*
* Purpose: adding an Item to the cart
******************************************************************************/
Item makeItem()
{
    string name;
    double price;
    int amount;

    cout << "What is the item name?" << endl;
    while(isspace(cin.peek()))
    {
        cin.ignore();
    }
    getline(cin, name);

    cout << "\nWhat price does this item have?" << endl;
    price = doubleCheck(0, INT_MAX, 2);

    cout << "\nHow many of this item do you want?" << endl;
    amount = intCheck(0,INT_MAX);

    Item object(name, price, amount);

    return object;
}

/******************************************************************************
* Entry: two double values used as range parameters for the user input, to
*        not use a range make min greater than max ie doubleCheck(1,0), as well
*        as an integer which represents the number of numbers after the decimal
*        point, to void this make it negative ie doubleCheck(,,-1)
*
* Exit: gets user input and checks that it is a single double with a precision
*       of maxCount after the decimal, ignores whitespace, and returns input if
*       it is a double between the given range if a range is given
*
* Purpose: getting and checking validity of 1 input
******************************************************************************/
double doubleCheck(double min, double max, int maxCount)
{
    string number; //user input
    int decimalCount; //number of numbers after decimal
    bool error; //input was not an int in given range
    bool numberThere; //user input had a number
    bool space; //user input had a space after a number
    bool decimal; //user input had a decimal

    //loops while input is not a number in given range
    do
    {
        decimalCount = 0;
        error = false;
        numberThere = false;
        space = false;
        decimal = false;
        getline(cin, number);

        //check that input is only 1 number, if so error = false,
        //numberThere = true
        for (int i = 0; i < number.length(); i++)
        {
            if (!isdigit(number[i]))
            {
                if (!decimal && number[i] == '.' && numberThere)
                    decimal = true; // found first period

                else if(!isspace(number[i]) && number[i] != '-' //found invalid char
                        || (!decimal && number[i] == '.' && !numberThere) //period before a digit
                        || (decimal && number[i] == '.') //a second period
                        || (number[i] == '-' && numberThere) //a negative after a digit
                        || (number[i] == '-' && i + 1 != number.length()
                            && !isdigit(number[i + 1]))) //negative is not before a digit

                    error = true;

                else if (numberThere && isspace(number[i]) && !space)
                    space = true; // found first space after number char
            }
            else
            {
                if (numberThere && space)
                    error = true; //found extra number
                else if (!numberThere)
                    numberThere = true; //found first number char
                else if (decimal && numberThere && !space)
                    decimalCount++;
            }
        }

        if (maxCount > 0 && decimalCount != maxCount)
            error = true;

        //ignore whitespace but if the input is wrong print error message
        if (number.empty() || (!numberThere && !error))
        {
            error = true;
        }
        else if (error)
        {
            cout << "\nPlease give only 1 double";

            if(maxCount > 0) //only ask for a specific form if maxCount is valid
            {
                cout << " of the form x.";
                for(int i = 0; i < maxCount; i++)//maxCount number of z's
                {
                    cout << "z";
                }
                cout << ", where x is any \ninteger and z is any"
                     << " digit";
            }
            cout << ", before hitting ENTER." << endl;
        }

        //if valid integer, check that it is in the given range
        if (!error && min < max)
        {
            int num = atof(number.c_str());
            if (num > max || num < min)
            {
                cout << setprecision(2) << showpoint;
                cout << "\nPlease give a double between " << min << " and "
                     << max << "." << endl;
                error = true;
            }
        }

    } while (error);

    return atof(number.c_str());
}

/******************************************************************************
* Entry: two integer values used as range parameters for the user input, to
*        not use a range make min greater than max ie intCheck(1,0)
*
* Exit: gets user input and checks that it is a single int, ignores whitespace,
*       and returns input if it is an integer between the given range if a
*       range is given
*
* Purpose: getting and checking validity of 1 input
******************************************************************************/
int intCheck(int min, int max)
{
    string number; //user input
    bool error; //input was not an int in given range
    bool numberThere; //user input had a number
    bool space; //user input had a space after a number

    //loops while input is not a number in given range
    do
    {
        error = false;
        numberThere = false;
        space = false;
        getline(cin, number);

        //check that input is only 1 number, if so error = false, numberThere = true
        for (int i = 0; i < number.length(); i++)
        {
            if(!isdigit(number[i]))
            {
                if (!isspace(number[i]) && number[i] != '-'
                    || (number[i] == '-' && numberThere))
                    error = true; //found nondigit that isn't whitespace
                else if (numberThere && isspace(number[i]) && !space)
                    space = true; //found first space after number
            }
            else
            {
                if (numberThere && space)
                    error = true; //found extra number
                else if (!numberThere)
                    numberThere = true; //found first number character
            }

        }

        //ignore whitespace but if the input is wrong print error message
        if (number.empty() || (!numberThere && !error))
            error = true;
        else if (error)
            cout << "\nPlease give only 1 integer before hitting ENTER." << endl;

        //if valid integer, check that it is in the given range
        if (!error && min < max)
        {
            int num = atoi(number.c_str());
            if (num > max || num < min)
            {
                cout << "\nPlease give an integer between " << min << " and " << max
                     << "." << endl;
                error = true;
            }
        }

    } while (error);

    return atoi(number.c_str());
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
