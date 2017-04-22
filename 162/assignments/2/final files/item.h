#include <string>
using std::string;

#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED
class Item
{
    private:
        string name; //name of item
        string type; //type of container
        double price; //price of the item
        int quantity; //number of item in cart

    public:

        Item();

        //initialize Item with given parameters
        Item(string n, string t, double pr, int qt)
        {
            name = n;
            type = t;
            price = pr;
            quantity = qt;
        }

        string getName() const //return name
        { return name; }

        string getType() const //return type
        { return type; }

        double getPrice() const //return price
        { return price; }

        int getAmount() const //return quantity
        { return quantity; }

        void addAmount(int qt)
        { quantity += qt; }

        void changePrice(double pr)
        { price = pr; }
};


#endif // ITEM_H_INCLUDED
