/*****************************************************************************************
** Program Filename: groceryList.cpp
** Author: Jennifer Frase
** Date: 2/1/15
** Description: create and/or modify grocery lists
** Input: items - their name, unit type, quantity, and unit price
          saved files of the form: name'\t'type'\t'quantity'\t'price'\n'
** Output: the list either to the screen or to a save file
*****************************************************************************************/

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <cstdlib>
using std::fixed;
using std::showpoint;

using std::left;
using std::right;

#include <climits>
#include <iomanip>
using std::setprecision;

#include <vector>
using std::vector;

#include <fstream>
using std::fstream;
using std::ios;

#include "int_check.h"
#include "response_check.h"
#include "double_check.h"
#include "item.h"

using std::setw;

Item makeItem();

int main()
{
    const int MAX_SIZE = 100; //maximum number of items in cart
    const int SCREEN_PUSH = 25; //print the number of lines to clear screen
    char response; //user input
    string space; // used to push output off the screen
    vector<Item> cart;

    space.assign(SCREEN_PUSH, '\n');

    cout << "Your shopping cart:" << endl;

    cout << "\nDo you want to read a list from a file" << endl;

    /* if the user want to open a file, get the file and write it to the list */
    if (responseCheck('Y', 'N', '\0', '\0') == 'Y')
    {
        string fileName;
        cout << "\nWhat is name of the file (w/o extension)?" << endl;
        getline(cin, fileName);
        fileName += ".txt";
        fstream readFile(fileName.c_str() , ios::in); //open input file

        while(!readFile.fail() && readFile.peek() != EOF )
        {
            string name,
                   type;
            int amount;
            double price;

            /* get next character until tab and add to name */
            while (readFile.peek() != '\t')
                name += readFile.get();

            readFile.get(); //get rid of \t

            /* get next character until tab and add to type */
            while (readFile.peek() != '\t')
                type += readFile.get();

            readFile >> amount; //get quantity
            readFile >> price; //get price
            readFile.get(); //get rid of \n

            Item object(name, type, price, amount);

            cart.push_back(object);
        }

        readFile.close();
    }
	
    //get user commands until they want to quit
    do
    {

        cout << "\nWhat do you want to do?\n"
             << "1) add/edit an item\n"
             << "2) remove item\n"
             << "3) show list\n"
             << "4) quit" << endl;
        response = responseCheck('1', '2', '3', '4');

        cout << space;

        if (response == '1') //add item
        {
            Item object = makeItem();
            bool prior = false;

            /*check if item is already in the cart, if so alter it's values*/
            for (int i = 0; i < cart.size(); i++)
            {
                if(object.getName() == cart[i].getName()
                   && object.getType() == cart[i].getType())
                {
                    cart[i].addAmount(object.getAmount());
                    cart[i].changePrice(object.getPrice());
                    prior = true;
                }
            }

            if(!prior)
                cart.push_back(object); //object wasn't in cart, so add it

        }
        else if (response == '2') //remove an item
        {
            string name, type;

            /*get item name ignoring leading space*/
            cout << "\nWhat is the item name?" << endl;
            while(isspace(cin.peek()))
            {
                cin.ignore();
            }
            getline(cin, name);

            /*get item name ignoring leading space*/
            cout << "\nWhat is the unit type?" << endl;
            while(isspace(cin.peek()))
            {
                cin.ignore();
            }
            getline(cin, type);

            /*get the position in the cart that item is at*/
            int position = -1;
            for (int i = 0; i < cart.size(); i++)
            {
                if(name == cart[i].getName()
                   && type == cart[i].getType())
                {
                    position = i;
                }
            }

            if(position >= 0)
                cart.erase(cart.begin() + position);
            else
                cout << "That item is not on the list." <<  endl;

        }
        else if (response == '3') //print list
        {

            double total = 0;
            double subtotal;
            cout << "ITEM                          TYPE    "
                 << "UNIT PRICE ($)   QUANTITY   SUBTOTAL ($)\n" << endl;

            //print items in cart
            for(int i = 0; i < cart.size(); i++)
            {
                cout << fixed << showpoint << setprecision(2) ;
                cout << left << setw(30) << cart[i].getName();
                cout << setw(12) << cart[i].getType();
                cout << setw(16) << cart[i].getPrice();
                cout << setw(11) << cart[i].getAmount();
                subtotal = cart[i].getPrice() * cart[i].getAmount();
                cout << subtotal << endl;
                total += subtotal;
            }

            cout << "\nTOTAL: $" << total << endl;

            cout << endl;
        }

        //wait till user wants to return to menu then push output off screen
        if (response != '4')
        {
            cout << "\nHit ENTER to go back." << endl;
            cin.get();
            cout << space;
        }

    }while (response != '4');

    cout << "Do you want to save the list?" << endl;

    /* save the list if the use wants to */
    if( responseCheck('Y', 'N', '\0', '\0') == 'Y')
    {
        string fileName;
        cout << "\nWhat file name (w/o extension) do you want to use?" << endl;
        getline(cin, fileName);
        fileName += ".txt";
        fstream writeFile(fileName.c_str() , ios::out);

        for (int i = 0; i < cart.size(); i++)
        {
            writeFile << cart[i].getName() << '\t'
                      << cart[i].getType() << '\t'
                      << cart[i].getAmount() << '\t'
                      << cart[i].getPrice() << '\n';
        }

        writeFile.close();
    }

    return 0;
}

/*****************************************************************************************
** Function: makeItem
** Description: creates a new Item from user input
** Parameters:  none
** Pre-Conditions: none
** Post-Conditions: none
*****************************************************************************************/
Item makeItem()
{
    string name,
           type;
    double price;
    int amount;

    cout << "To edit an existing item: type in the item's name and type,\n"
         << "then the new price is what you enter, and the quantity you\n"
         << "enter is added to the existing quantity\n"
         << endl;

    cout << "What is the item name?" << endl;
    while(isspace(cin.peek()))
    {
        cin.ignore();
    }
    getline(cin, name);

    cout << "\nWhat is the unit type?" << endl;
    while(isspace(cin.peek()))
    {
        cin.ignore();
    }
    getline(cin, type);

    cout << "\nWhat price does this item have?" << endl;
    price = doubleCheck(0, INT_MAX, 2);

    cout << "\nHow many of this item do you want?" << endl;
    amount = intCheck(0,-1);

    Item object(name, type, price, amount);

    return object;
}
