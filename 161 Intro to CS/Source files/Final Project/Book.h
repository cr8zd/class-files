//
//  Book.h
//  examples
//
//  Created by Tim Alcon on 11/25/14.
//  Copyright (c) 2014 Tim Alcon. All rights reserved.
//
// altered by Jennifer Frase - see comments in .cpp file

#ifndef examples_Book_h
#define examples_Book_h

class Patron;

enum Locale {ON_SHELF, ON_HOLD, CHECKED_OUT};

class Book
{
private:
    std::string idCode; //unique identifier
    std::string title; //title of book
    std::string author; //author of book
    Locale location; //where the book is
    Patron* checkedOutBy; //person who currently checked out book
    Patron* requestedBy; //person who currently wants the book
    int dateCheckedOut; //day book was checked out
public:
    static const int CHECK_OUT_LENGTH = 21; //number of days checked out until overdue

    Book();
    Book(std::string idc, std::string t, std::string a);

    std::string getIdCode() //return idCode
    { return idCode; }

    std::string getTitle() //return title
    { return title; }

    std::string getAuthor() //return author
    { return author; }

    Locale getLocation() //return location
    { return location; }

    void setLocation(Locale lo) //set location
    { location = lo; }

    Patron* getCheckedOutBy() //return pointer to Patron that checked out the book
    { return checkedOutBy; }

    void setCheckedOutBy(Patron* p) //set checkedOutBy
    { checkedOutBy = p; }

    Patron* getRequestedBy() //return pointer to Patron who requested the book
    { return requestedBy; }

    void setRequestedBy(Patron* p) //set requestedBy
    { requestedBy = p; }

    int getDateCheckedOut() //return dateCheckedOut
    { return dateCheckedOut; }

    void setDateCheckedOut(int d) //set dateCheckedOut
    { dateCheckedOut = d; }
};

#endif
