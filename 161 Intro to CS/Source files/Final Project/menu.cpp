/******************************************************************************
* Author: Jennifer Frase
* Date Created: 12/2/14
* Last Modification Date: 12/3/14
* Filename: menu.cpp
*
* Overview:
* This program will create a Library object and then allow the user to use
* the library's functions to do various tasks such as add a book or see a
* member's information or increase the date.
*
* Input:
* The input will be member and book id's as well as amounts a member wants
* to pay back, as well as input found in the library functions.
*
* Output:
* The output for this program will be a menu of options for the user to pick
* from as well as any output from the library functions.
******************************************************************************/

#include <iostream>
#include <climits>
#include "Library.h"
#include "Patron.h"
#include "Book.h"

using namespace std;

/******************************************************************************
* Entry: There is one parameter a string which is the type of id the function
*        is getting
*
* Exit: gets the user's input for what id is being checked based on the option
*       picked return the user input
*
* Purpose: getting the an id for the library function to check against
******************************************************************************/
string getId(string name)
{
    string id; //user input for id of object

    cout << "What is the " << name << "'s ID?" << endl;

    //ignore enter presses
    do
    {
        getline(cin, id);
    }while(id.empty());

    return id;
}

int main()
{
    const int SCREEN_PUSH = 25; //print the number of lines to clear screen
    string space; //used to push the output off screen
    char response; //user response to menu
    Library bookshelf; //library with which the user is using

    space.assign(SCREEN_PUSH, '\n');

    //get user commands until they want to quit
    do
    {
        cout << "Library Options:\n" << endl;
        cout << "1) add a book\n"
             << "2) add a member\n"
             << "3) check out a book\n"
             << "4) return a book\n"
             << "5) request a book\n"
             << "6) pay a fine\n"
             << "7) increment date\n"
             << "8) view member info\n"
             << "9) view book info\n"
             << "0) quit" << endl;
        cout << "\nWhat do you want to do?" << endl;
        cin >> response;
        cin.ignore(INT_MAX, '\n');

        cout << space;

        //call appropriate library function
        switch(response)
        {
            case '1': bookshelf.addBook();
                      break;
            case '2': bookshelf.addMember();
                      break;
            case '3':
                {
                    string bookId3 = getId("book");
                    string memberId3 = getId("member");
                    bookshelf.checkOutBook(memberId3, bookId3);
                    break;
                }
            case '4':
                {
                    string bookId4 = getId("book");
                    bookshelf.returnBook(bookId4);
                    break;
                }
            case '5':
                {
                    string bookId5 = getId("book");
                    string memberId5 = getId("member");
                    bookshelf.requestBook(memberId5, bookId5);
                    break;
                }
            case '6':
                {
                    string memberId6 = getId("member");
                    cout << "How much do you want to pay?" << endl;
                    double payment;
                    cin >> payment;
                    cin.ignore(INT_MAX, '\n');
                    bookshelf.payFine(memberId6, payment);
                    break;
                }
            case '7':
                {
                    bookshelf.incrementCurrentDate();
                    break;
                }
            case '8':
                {
                    string memberId8 = getId("member");
                    bookshelf.viewPatronInfo(memberId8);
                    break;
                }
            case '9':
                {
                    string bookId9 = getId("book");
                    bookshelf.viewBookInfo(bookId9);
                    break;
                }
            case '0': break;
            default : cout << "That is not a valid option." << endl;
        }


        if (response != '0')
        {
            cout << "\nHit ENTER to go back." << endl;
            cin.get();
            cout << space;
        }

    }while (response != '0');

    return 0;
}
