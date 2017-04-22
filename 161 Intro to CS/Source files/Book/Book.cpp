#include <iostream>
#include "Book.h"

Book::Book(string idc, string t, string a)
{
    idCode = idc;
    title = t;
    author = a;
    checkedOutBy = NULL;
    requestedBy = NULL;
}
