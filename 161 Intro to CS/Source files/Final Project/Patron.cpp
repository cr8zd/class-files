/******************************************************************************
* Author: Jennifer Frase
* Date Created: 12/1/14
* Last Modification Date: 12/3/14
* Filename: Patron.cpp for Patron.h
*
* Overview:
* This program and header file will create a Patron class for a library where
* the Patron is the information of library users.
*
* Input:
* There is no input for this program/header.
*
* Output:
* There is no output for this program/header.
******************************************************************************/

#include <string>
#include "Patron.h"
#include "Book.h"

/******************************************************************************
* Entry: There is one parameter a pointer to a Book
*
* Exit: erases the passed Book from checkedOutBooks
*
* Purpose: removing a book from checkedOutBooks
******************************************************************************/
void Patron::removeBook(Book* b)
{
    for(int i = 0; i < checkedOutBooks.size(); i++)
    {
        if (checkedOutBooks[i]->getIdCode() == b->getIdCode())
            checkedOutBooks.erase(checkedOutBooks.begin() + i);
    }
}

