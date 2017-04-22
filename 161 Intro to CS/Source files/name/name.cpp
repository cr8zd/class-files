/******************************************************************************
* Author: Jennifer Frase
* Date Created: 10/16/14
* Last Modification Date: 10/17/14
* Filename: name.cpp
*
* Overview:
* This program will take a users name and print is out.
* It will control for excess spaces in the name, more
* than one word in the last name, and capitalization of
* the first letter of names.
*
* Input:
* The input will be a string which is the users name:
* first name, middle name/initial, last name
* If last name has spaces in it, the user will have to
* either input last name again or confirm the words in the
* name are not middle names.
*
* Output:
* The output for this program will be the users name:
* last name, first name, middle initial
* If there are more than 1 space in name, user will
* be asked what their last name is or if the second
* word given is their middle name.
******************************************************************************/

#include <iostream>
#include <string>

using namespace std;

int main()
{
    string name, //user input of name
           firstName, //first word in user input
           lastName; //all words in the last name
    char middleInitial; //first letter of middle name
    bool middleName = false; //is there a middle name
    int spaces = 0, //counter for spaces in name
        space1 = 0, //position of first space, marks end of first name
        space2 = 0; // position of second space, marks end of second word

    // asks for a name, has to have at least 1 space
    do
    {
        cout << "Please give me your name." << endl;
        getline(cin, name);

        name[0] = toupper(name[0]);

        //gets rid of excess spaces, counts remaining spaces,
        //and capitalizes first letter of each name
        for (int i = name.length() - 1; i >= 0; i--)
        {
            if (name[i] == ' ')
            {
                if (i == name.length() -1 || i == 0)
                {
                    name.erase(i, 1);
                }
                else if (name[i - 1] == ' ')
                {
                    name.erase(i - 1, 1);
                }
                else
                {
                    spaces++;
                    name[i + 1] = toupper(name[i + 1]);
                }
            }
        }
        if (spaces == 0)
        {
            cout << "You need to give me a first and last name"
                 << "\nminimum, with spaces in between." << endl;
        }
    } while (spaces == 0);

    space1 = name.find(' ', 0);
    firstName.assign(name, 0, space1 + 1);

    // figures out what the last name is and if there is a middle name
    // accounts for multiple last name words
    if (spaces > 2) // first name, middle name?, multiple last name
    {
        cout << "I assume " << firstName << " is your "
             << "first name." << endl;

        // makes sure that given last name was in original name
        do
        {
            cout << "\nPlease give the exact same last name"
                 << " as the original. The name you gave"
                 << "\noriginally was " << name << "." << endl;
            getline(cin, lastName);

            //capitalizes first letter of each name and erases excess spaces
            lastName[0] = toupper(lastName[0]);
            for (int i = lastName.length() - 1; i >= 0; i--)
            {
                if (lastName[i] == ' ')
                {
                    if (i == lastName.length() -1 || i == 0)
                    {
                        lastName.erase(i, 1);
                    }
                    else if (lastName[i - 1] == ' ')
                    {
                        lastName.erase(i - 1, 1);
                    }
                    else
                    {
                        lastName[i + 1] = toupper(lastName[i + 1]);
                    }
                }
            }
        } while (name.find(lastName, space1) == string::npos || lastName.empty());

        //set middleName to true when more names than the first and last
        (name.find(lastName, space1) - space1 == 1)?
            middleName = false : middleName = true;
    }
    else if (spaces == 2) // first name, middle name?, last name
    {
        string confirm;

        middleName = true;
        space2 = name.find(' ', space1 + 1);
        lastName.assign(name, space2 + 1, name.length() - (space2 + 1));

        // makes sure the second name is not part of last name
        if (name[space1+2] == ' ' || name[space1+2] == '.')
            middleName = true;
        else
        {
            cout << "Is " << name.substr(space1 + 1, space2 - space1 - 1) << " your middle name? Yes or no?";
            getline(cin, confirm);
            if (toupper(confirm[0]) != 'Y')
            {
                lastName.assign(name, space1 + 1, name.length() - (space1 + 1));
                middleName = false;
            }
        }


    }
    else if (spaces == 1) // first name, last name
    {
        lastName.assign(name, space1 + 1, name.length() - (space1 + 1));
    }
    else //error check didn't work
    {
        cout << "You had an error.";
    }

    // if middle initial, assigns it; does not account for multiple middle names
    if(middleName)
    {
        middleInitial = name[space1 + 1];
    }

    //print name
    cout << "\nYour name is: " << lastName << ", "
         << firstName << " ";
    if (middleName)
        cout << middleInitial << ".";
    cout << endl;

    return 0;
}
