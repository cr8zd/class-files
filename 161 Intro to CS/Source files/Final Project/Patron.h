//
//  Patron.h
//  examples
//
//  Created by Tim Alcon on 11/25/14.
//  Copyright (c) 2014 Tim Alcon. All rights reserved.
//
// altered by Jennifer Frase - see comments in .cpp file

#ifndef __examples__Patron__
#define __examples__Patron__

#include <stdio.h>
#include <vector>

class Book;

class Patron
{
private:
    std::string idNum; //unique identifier
    std::string name; //person's name
    std::vector<Book*> checkedOutBooks; //books person currently has checked out
    double fineAmount; //amount owed to the library for overdue books

public:
    Patron() //default constructor
    { fineAmount = 0; }

    Patron(std::string idn, std::string n) //initialize member variables
    { idNum = idn, name = n, fineAmount = 0;}

    std::string getIdNum() //return idNum
    { return idNum; }

    std::string getName() //return name
    { return name; }

    std::vector<Book*> getCheckedOutBooks() //return checkedOutBooks
    { return checkedOutBooks; }

    void addBook(Book* b) //add a book to checkedOutBooks
    { checkedOutBooks.push_back(b); }

    void removeBook(Book* b);

    double getFineAmount() //return fineAmount
    { return fineAmount; }

    void amendFine(double amount) //add passed in amount to fineAmount
    { fineAmount += amount; }
};

#endif /* defined(__examples__Patron__) */
