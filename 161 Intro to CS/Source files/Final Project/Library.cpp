/******************************************************************************
* Author: Jennifer Frase
* Date Created: 12/2/14
* Last Modification Date: 12/3/14
* Filename: Library.cpp for Library.h
*
* Overview:
* This program and header file will create a Library class that will store
* information on books and members as well as do various library functions
* such as checking out a book or adding members.
*
* Input:
* The input will be information on new books and new members.
*
* Output:
* The output will be what each function has done or the information on a
* member or book.
******************************************************************************/

#include <iostream>
#include <iomanip>
#include "Library.h"
#include "Book.h"
#include "Patron.h"

using namespace std;

/******************************************************************************
* Entry: none
*
* Exit: initializes currentDate and increases the capacity of holdings and
*       members to 100
*
* Purpose: default constructor
******************************************************************************/
Library::Library()
{
    currentDate = 0;
    holdings.reserve(100);
    members.reserve(100);
}

/******************************************************************************
* Entry: None
*
* Exit: gets the information on a book and adds the book to the holdings vector
*
* Purpose: adding a book to the library
******************************************************************************/
void Library::addBook()
{
    string idCode, title, author; // book information

    cout << "What is the book's ID code?" << endl;
    getline(cin, idCode);

    //check if ID is unique
    for(int i = 0; i < holdings.size(); i++)
    {
        if(holdings[i].getIdCode() == idCode)
        {
            cout << "That ID is already in use." << endl;
            return;
        }
    }

    cout << "\nWhat is the title of the book?" << endl;
    getline(cin, title);
    cout << "\nWho is the author of the book?" << endl;
    getline(cin, author);
    Book newBook(idCode, title, author);
    holdings.push_back(newBook);
}

/******************************************************************************
* Entry: None
*
* Exit: gets the information on a new member and adds that member to the
*       library's members vector
*
* Purpose: adding a member to the library
******************************************************************************/
void Library::addMember()
{
    string idCode, name; // patron information

    cout << "What is the member's ID code?" << endl;
    getline(cin, idCode);

    //check if ID is unique
    for(int i = 0; i < members.size(); i++)
    {
        if(members[i].getIdNum() == idCode)
        {
            cout << "That ID is already in use." << endl;
            return;
        }
    }

    cout << "\nWhat is the member's name?" << endl;
    getline(cin, name);
    Patron newMem(idCode, name);
    members.push_back(newMem);
}

/******************************************************************************
* Entry: There are two string parameters, where the first is the member id
*        of the Patron wanting to check out a book, and the second is the
*        book id of the book wanting to be checked out
*
* Exit: determines where the book can be checked out by the member and if so
*       changes the books location and adds the book to that member's
*       check out books list
*
* Purpose: checking out a book
******************************************************************************/
void Library::checkOutBook(string patronID, string bookID)
{
    Patron* member = memberCheck(patronID); // pointer to member with matching ID
                                            // NULL if nonexistent
    Book* book = bookCheck(bookID); // pointer to book with matching ID
                                    // NULL if nonexistent
    //check if person can check out the book
    if(member == NULL)
    {
        cout << "\nThat is an invalid member ID." << endl;
    }
    else if(book == NULL)
    {
        cout << "\nThat book is not a part of this library." << endl;
    }
    else if(book->getLocation() == 2)
    {
        cout << "\nThat book is already checked out." << endl;
    }
    else if(book->getLocation() == 1
            && book->getRequestedBy()->getIdNum() != member->getIdNum())
    {
        cout << "\nThat book is on hold by another member." << endl;
    }
    else
    {
        book->setCheckedOutBy(member);
        book->setDateCheckedOut(currentDate);
        book->setLocation(CHECKED_OUT);
        if (book->getLocation() == 1)
            book->setRequestedBy(NULL);
        member->addBook(book);
        cout << "\n" << book->getTitle() << " has been checked out by "
             << member->getName() << "." << endl;
    }
}

/******************************************************************************
* Entry: There is one parameter a string of a book's id code
*
* Exit: determines if the book can be returned and if so changes it's location
*       to the appropriate place and removes the book for the appropriate
*       member's checked out book list
*
* Purpose: returning a book to the library
******************************************************************************/
void Library::returnBook(string bookID)
{
    Book* book = bookCheck(bookID); // pointer to book with matching ID
                                    // NULL if nonexistent
    if(book == NULL)
    {
        cout << "\nThat book is not a part of this library." << endl;
    }
    else if(book->getLocation() != 2)
    {
        cout << "\nThat book is not checked out." << endl;
    }
    else
    {
        Patron* member = book->getCheckedOutBy();
        member->removeBook(book);

        if(book->getRequestedBy() != NULL)
            book->setLocation(ON_HOLD);
        else
            book->setLocation(ON_SHELF);

        book->setCheckedOutBy(NULL);
        cout << "\n" << book->getTitle() << " has been returned." << endl;
    }
}

/******************************************************************************
* Entry: There are two string parameters where the first is the member id of
*        the person wanting the book and the second is the book id of the book
*        the member is wanting
*
* Exit: checks if the member can request the book and if so sets the book's
*       requestedBy to that member
*
* Purpose: requesting a book to be put on the hold shelf
******************************************************************************/
void Library::requestBook(string patronID, string bookID)
{
    Patron* member = memberCheck(patronID); // pointer to member with matching ID
                                            // NULL if nonexistent
    Book* book = bookCheck(bookID); // pointer to book with matching ID
                                    // NULL if nonexistent
    if(member == NULL)
    {
        cout << "\nThat is not a valid member ID." << endl;
    }
    else if(book == NULL)
    {
        cout << "\nThat book is not a part of this library." << endl;
    }
    else if(book->getRequestedBy() != NULL)
    {
        cout << "\nThat book is on hold by another member." << endl;
    }
    else
    {
        book->setRequestedBy(member);
        if(book->getLocation() == 0)
            book->setLocation(ON_HOLD);
        cout << "\n" << book->getTitle() << " has been requested by "
             << member->getName() << "." << endl;
    }
}

/******************************************************************************
* Entry: None
*
* Exit: increments the number of days since the library was created and adds
*       to the fineAmount of any member with an overdue book
*
* Purpose: changing the date and adjusting fine amounts as needed
******************************************************************************/
void Library::incrementCurrentDate()
{
    currentDate++;
    for(int i = 0; i < holdings.size(); i++)
    {
        if( holdings[i].getLocation() == 2 &&
           ((currentDate - holdings[i].getDateCheckedOut()) > Book::CHECK_OUT_LENGTH))
        {
            holdings[i].getCheckedOutBy()->amendFine(DAILY_FINE);
        }
    }
    cout << "The date is now " << currentDate << "." << endl;
}

/******************************************************************************
* Entry: There are two parameter, one string of the member id wanting to pay
*        back on their fine, and one double which is the amount they want to
*        pay
*
* Exit: changes the member's fineAmount by the negative of the double passed
*
* Purpose: paying back on a fine
******************************************************************************/
void Library::payFine(string patronID, double payment)
{
    Patron* member = memberCheck(patronID); // pointer to member with matching ID
                                            // NULL if nonexistent

    if(member == NULL)
    {
        cout << "\nThat is an invalid member ID" << endl;
    }
    else
    {
        member->amendFine(0 - payment);
        cout << "\nThe fines for " << member->getName()
             << " are now $" << fixed << showpoint << setprecision(2)
             << member->getFineAmount() << "." << endl;
    }
}

/******************************************************************************
* Entry: There is one parameter a string which is a member's id
*
* Exit: prints the information of the member with the passed in member id
*
* Purpose: printing a member's information
******************************************************************************/
void Library::viewPatronInfo(string patronID)
{
    Patron* member = memberCheck(patronID); // pointer to member with matching ID
                                            // NULL if nonexistent
    string line; //used to print a line
    line.assign(20, '-');

    if(member == NULL)
    {
        cout << "\nThe is an invalid member ID" << endl;
    }
    else
    {
        cout << left << setw (16) << "\nID NUMBER:" << member->getIdNum()
             << "\n" << endl;
        cout << setw(15) << "NAME:" << member->getName() << endl;
        cout << setw (15) << "\nCHECKED OUT BOOKS:" << endl;
        cout << line << endl;
        for(int i = 0; i < member->getCheckedOutBooks().size(); i++)
        {
            cout << setw (20) << member->getCheckedOutBooks()[i]->getTitle()
                 << endl;
            cout << line << endl;
        }
        cout << "\nCURRENT FINES: $" << fixed << showpoint << setprecision(2)
             << member->getFineAmount() << endl;
    }
}

/******************************************************************************
* Entry: There is one parameter a string which is a book's id
*
* Exit: prints the information of the book with the passed in book id
*
* Purpose: printing a book's information
******************************************************************************/
void Library::viewBookInfo(string bookID)
{
    Book* book = bookCheck(bookID); // pointer to book with matching ID
                                    // NULL if nonexistent
    if(book == NULL)
    {
        cout << "\nThat book is not a part of this library" << endl;
    }
    else
    {
        cout << left << setw(21) << "\nID CODE:" << book->getIdCode()
             << "\n" << endl;
        cout << setw(20) << "TITLE:" << book->getTitle() << "\n" << endl;
        cout << setw(20) << "AUTHOR" << book->getAuthor() << "\n" << endl;
        cout << setw(20) << "LOCATION";
        if(book->getLocation() == 0)
        {
            cout << "On the shelf\n" << endl;
        }
        else if(book->getLocation() == 1)
        {
            cout << "On hold\n" << endl;
        }
        else
        {
            cout << "Checked out\n" << endl;
            cout << setw(20) << "CHECKED OUT BY:" << book->getCheckedOutBy()->getName()
                 << "\n" << endl;
            cout << setw (20) << "DUE DATE:"
                 << (book->getDateCheckedOut() + book->CHECK_OUT_LENGTH) << "\n"
                 << endl;
        }
        if(book->getRequestedBy() != NULL)
        {
            cout << setw(20) << "REQUESTED BY:" << book->getRequestedBy()->getName()
                 << endl;
        }
    }
}

/******************************************************************************
* Entry: There is one parameter a string which is a member's id
*
* Exit: finds the member with the matching id and return a pointer to that
*       member
*
* Purpose: getting the matching member out of the members vector
******************************************************************************/
Patron* Library::memberCheck(string patronID)
{
    int memberPos = -1; //position of member with matching ID

    for(int i = 0; i < members.size(); i++)
    {
        if(members[i].getIdNum() == patronID)
        {
            memberPos = i;
        }
    }
    if(memberPos < 0)
        return NULL;
    else
        return &members[memberPos];
}

/******************************************************************************
* Entry: There is one parameter a string which is a book's id
*
* Exit: finds the book with the matching id and return a pointer to that book
*
* Purpose: getting the matching book out of the holdings vector
******************************************************************************/
Book* Library::bookCheck(string bookID)
{
    int bookPos = -1; //position of book with matching ID

    for(int i = 0; i < holdings.size(); i++)
    {
        if(holdings[i].getIdCode() == bookID)
        {
            bookPos = i;
        }
    }
    if(bookPos < 0)
        return NULL;
    else
        return &holdings[bookPos];
}
