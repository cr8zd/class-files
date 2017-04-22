//
//  Patron.h
//  examples
//
//  Created by Tim Alcon on 11/25/14.
//  Copyright (c) 2014 Tim Alcon. All rights reserved.
//

#ifndef __examples__Patron__
#define __examples__Patron__

#include <stdio.h>
#include <vector>

using namespace std;

class Book;

class Patron
{
private:
    string idNum;
    string name;
    vector<Book*> checkedOutBooks;
    double fineAmount;
public:
    Patron(){};
    Patron(string idn, string n)
    { idNum = idn, name = n; }
    string getIdNum()
    { return idNum; }
    string getName()
    { return name; }
    vector<Book*> getCheckedOutBooks()
    { return checkedOutBooks; }
    void addBook(Book* b)
    { checkedOutBooks.push_back(b); }
    void removeBook(Book* b);
    double getFineAmount()
    { return fineAmount; }
    void amendFine(double amount)
    { fineAmount += amount; }
};

#endif /* defined(__examples__Patron__) */
