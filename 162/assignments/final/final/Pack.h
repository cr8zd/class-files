/*****************************************************************************************
** Program Filename: Pack.h
** Author: Jennifer Frase
** Date: 3/17/15
** Description: creates a struct of items that have a name and size, it then creates
**              a class to hold and deal with the items. Given them special care in
**              some cases.
**              Mainly for use with 7 max bag, but to use otherwise you just have to
**              alter the limit away from 7.
*****************************************************************************************/
#include <iostream>
#include <string>

#ifndef PACK_H_INCLUDED
#define PACK_H_INCLUDED


/*****************************************************************************************
** Name: Item
** Description: groups together the size and name of objects
*****************************************************************************************/
struct Item
{
    std::string name;
    int size;

    Item()
    {
        name = "empty", size = 0;
    }

    Item(std::string n, int s)
    {
        name = n, size = s;
    }

    void operator=(Item &newItem)
    {
        name = newItem.name;
        size = newItem.size;
    }
};

class Pack
{
private:
    Item pack[15];
    int sizeLimit;
public:
    Pack()
    { sizeLimit = 7; }

    void setLimit(int limit)
    { sizeLimit = limit; }

    Item& operator[](int value)
    {
        return pack[value];
    }

    bool addItem(Item newItem);
    void removeItem(Item old);
};


#endif // PACK_H_INCLUDED
