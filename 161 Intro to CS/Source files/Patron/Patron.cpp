#include <iostream>
#include "Patron.h"
#include "Book.h"

void Patron::removeBook(Book* b)
{
    for(int i = 0; i < checkedOutBooks.size(); i++)
    {
        if (checkedOutBooks[i]->getIdCode() == b->getIdCode())
            checkedOutBooks.erase(checkedOutBooks.begin() + i);
    }
}
