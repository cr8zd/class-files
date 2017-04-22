/******************************************************************************
* Author: Jennifer Frase
* Date Created: 12/1/14
* Last Modification Date: 12/3/14
* Filename: Book.cpp for Book.h
*
* Overview:
* This program and header file will create a Book class for a library where
* a Book stores the information on a single book in the library.
*
* Input:
* There is no input for this program/header.
*
* Output:
* There is no output for this program/header.
******************************************************************************/

#include <string>
#include "Book.h"
#include "Patron.h"

/******************************************************************************
* Entry: There are no parameters
*
* Exit: initializes variables that are always the same for every new book
*
* Purpose: default constructor
******************************************************************************/
Book::Book()
{
    location = ON_SHELF;
    checkedOutBy = NULL;
    requestedBy = NULL;
    dateCheckedOut = -1;
}

/******************************************************************************
* Entry: There are three string parameters, where the first is the unique
*        identifier for the book, the second is the title of the book, and the
*        the third is the author of the book
*
* Exit: initializes books information
*
* Purpose: constructor with arguments
******************************************************************************/
Book::Book(std::string idc, std::string t, std::string a)
{
    idCode = idc;
    title = t;
    author = a;
    location = ON_SHELF;
    checkedOutBy = NULL;
    requestedBy = NULL;
    dateCheckedOut = -1;
}
