//
//  Library.h
//  examples
//
//  Created by Tim Alcon on 11/25/14.
//  Copyright (c) 2014 Tim Alcon. All rights reserved.
//
// altered by Jennifer Frase - see comments in .cpp file

#ifndef __examples__Library__
#define __examples__Library__

#include <vector>
#include <stdio.h>

using namespace std;

class Patron;
class Book;

class Library
{
private:
    vector<Book> holdings; //vector of books in the library
    vector<Patron> members; //vector of members of the library
    int currentDate; //day since the library was created

    //private functions
    Patron* memberCheck(string patronID);
    Book* bookCheck(string bookID);

public:
    static const double DAILY_FINE = 0.1;
    Library();

    //public functions
    void addBook();
    void addMember();
    void checkOutBook(string patronID, string bookID);
    void returnBook(string bookID);
    void requestBook(string patronID, string bookID);
    void incrementCurrentDate();
    void payFine(string patronID, double payment);
    void viewPatronInfo(string patronID);
    void viewBookInfo(string bookID);
};

#endif /* defined(__examples__Library__) */
