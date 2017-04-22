//
//  Book.h
//  examples
//
//  Created by Tim Alcon on 11/25/14.
//  Copyright (c) 2014 Tim Alcon. All rights reserved.
//

#ifndef examples_Book_h
#define examples_Book_h

using namespace std;

class Patron;

enum Locale {ON_SHELF, ON_HOLD, CHECKED_OUT};

class Book
{
private:
    string idCode;
    string title;
    string author;
    Locale location;
    Patron* checkedOutBy;
    Patron* requestedBy;
    int dateCheckedOut;
public:
    static const int CHECK_OUT_LENGTH = 21;

    Book(){};
    Book(string idc, string t, string a);

    int getCheckOutLength()
    { return CHECK_OUT_LENGTH; }
    string getIdCode()
    { return idCode; }
    string getTitle()
    { return title; }
    string getAuthor()
    { return author; }
    Locale getLocation()
    { return location; }

    void setLocation(Locale lo)
    { location = lo; }
    Patron* getCheckedOutBy()
    { return checkedOutBy; }
    void setCheckedOutBy(Patron* p)
    { checkedOutBy = p; }
    Patron* getRequestedBy()
    { return requestedBy; }
    void setRequestedBy(Patron* p)
    { requestedBy = p; }
    int getDateCheckedOut()
    { return dateCheckedOut; }
    void setDateCheckedOut(int d)
    { dateCheckedOut = d; }
};

#endif
