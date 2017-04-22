/******************************************************************************
* Author: Jennifer Frase
* Date Created: 10/19/14
* Last Modification Date: 10/22/14
* Filename: secretWord.cpp
*
* Overview:
* This program will play a word guessing game. A user picks a secret word
* and another user tries to figure out what the word is by picking letters
* or picking numbers that represent randomized letters.
*
* Input:
* The input will be a variety of question answer responses that decide
* how the game will progress. In addition, one user will input a secret
* word, and another user will repeated input either a letter or number.
*
* Output:
* The output for this program will be prompts for letters and what letters
* were picked. At the end of a game the results will the be displayed as
* well as any missing letter.
******************************************************************************/

#include <iostream>
#include <string>
#include <cstdio>
#include <climits>
#include <iomanip>

using namespace std;

//prints evenly space characters from a string
void PrintList(string userList);

//checks that a response is valid for up to 3 valid inputs
char ResponseCheck(char valid1, char valid2, char valid3);

//empties the input stream and resets the flags
void CinEmpty();

int main()
{
    const int SCREEN_PUSH = 20; //print the number of lines to clear screen
    const int MIN_ROUNDS = 15; // minimum possible number of rounds
    const int MAX_ROUNDS = 20; // maximum possible number of rounds
    const char PLACE_HOLD = '.'; //character used in place of a characters
                                 //in the string CHARACTERS
    const string CHARACTERS =
            "abcdefghijklmnopqrstuvwxyz"; //possible characters in game
    string secret, // secret word user inputs
           guess, //the current guess user 2 thinks the secret is
           past, // past characters from CHARACTERS that have been picked
           actor, //still active char from CHARACTERS in random assortment
           space; //lines between output
    char letter, //user 2's letter pick
         response; // response to picking from a list ie Y or N
    int maxround, //actual max number of rounds for a game
        round, //number of rounds left in a game
        points; //points accumulated in a game

    space.assign(SCREEN_PUSH, '\n');

    //loop while player wants to play a game
    do
    {
        //clear or reinitialize variable for new game
        actor.clear();
        past.clear();
        secret.clear();
        points = 0;
        maxround = MIN_ROUNDS;

        //construct actor
        for(int i = 0; i < CHARACTERS.length(); i++)
        {
            actor += CHARACTERS.at(i);
        }

        bool isNotLetters = true; //true if char in secret aren't letters

        //get secret word
        while(secret.empty() || isNotLetters)
        {
            cout << "Please give me a secret word." << endl;
            getline(cin, secret);
            isNotLetters = false;

            for (int i = 0; i < secret.length(); i++)
            {
                if(!isalpha(secret[i]))
                    isNotLetters = true;
            }
        }

        //make all letter lowercase
        for(int i = 0; i < secret.length(); i++)
        {
            tolower(secret.at(i));
        }

        //determine maxround and set round
        if (secret.length() / 2 > MIN_ROUNDS)
            maxround = secret.length() / 2;

        if (maxround > MAX_ROUNDS)
            maxround = MAX_ROUNDS;

        round = maxround;
        guess.assign(secret.length(), PLACE_HOLD);
        cout << space;

        //plays a round of picking letters
        while (round > 0 && guess.compare(secret) != 0)
        {
            //prints what user thinks secret word is so far and the number of
            // rounds left
            cout << "\nYour guess so far is:\n" << guess
                 << "\n\nYou have " << round << " round"
                 << (round == 1? "" : "s") << " left." << endl;
            cout << "\nPick a letter from the list below." << endl;
            PrintList(actor);

            cout << endl;

            while((letter = cin.get()) == '\n')
            {}

            while(actor.find(letter) == string::npos)
            {
                cout << "Please give a letter from the list." << endl;
                while( (letter = cin.get()) == '\n')
                {}
            }
            actor.erase(actor.begin() + actor.find(letter));
            round--;

            bool inWord = false; //letter was in secret word
            past += letter;

            for (int i = 0;i < secret.length(); i++)
            {
                if (letter == secret.at(i))
                {
                    guess.at(i) = letter;
                    inWord = true;
                    points++;
                }
            }

            //print appropriate message depending on whether they
            //found a letter
            if (inWord)
            {
                cout << "\nYour guess was in the secret word!\n"
                     << "\nYour guess is now:\n" << guess << endl;
            }
            else if (guess != secret)
            {
                cout << "\nYour guess was not in the secret word.";
                inWord = true;
            }

            //guess != secret, so ask for another round
            if (inWord)
            {
                cin.get();
                CinEmpty();
            }

            cout << space;
        }

        cout << "\nThe secret word was " << secret << endl;

        //print they found the word and how many extra points they get
        if (guess == secret)
        {
            cout << "\nCongratulations, you found the secret word!"
                 << "\nYou get " << actor.length() << " extra point"
                 << (actor.length() == 1? "" : "s") << " remaining"
                 << endl;
            points += actor.length();
        }
        //print they lost and what letters needed to be found
        else
        {
            string missing; //characters not picked from the secret word

            cout << "\nYou lost. You still needed to find:" << endl;

            //finds missed letters and adds it to missing
            for(int i = 0; i < guess.length(); i++)
            {
                char missed = NULL; //missed letter in secret

                //gets missed letter
                if (guess.at(i) == PLACE_HOLD)
                    missed = secret.at(i);

                //adds letter to missing if not already there
                if (missed != NULL)
                {
                    if (missing.find(missed) == string::npos)
                        missing += missed;
                }
            }

            PrintList(missing);
        }

        //add points to total and print points earn and new total
        cout << "\nYou earned " << points << " point"
             << (points == 1? "" : "s") << " in this game."
             << endl;

        //figure out if they want to play another game
        cout << "\nDo you want to play again?" << endl;
        response = ResponseCheck('Y', 'N', NULL);
        cout << space;

    }while (toupper(response) != 'N');

    return 0;
}

/******************************************************************************
* Entry: any string
*
* Exit: Seperate and print each character in userList
*
* Purpose: Display the characters in userList
*
******************************************************************************/
void PrintList(string userList)
{
    for(int i = 0; i < userList.length(); i++)
    {
        cout << left << setw(4) << userList.at(i);

        //creates new line ever 7th character
        if ((i + 1) % 7 == 0)
            cout << endl;
    }
}

/******************************************************************************
* Entry: Three char values for which the function can check against, can be
*        NULL
*
* Exit: gets user input and compares it to the valid responses until it final
*       gets a valid response
*
* Purpose: checking that a response is valid
*
******************************************************************************/
char ResponseCheck(char valid1, char valid2, char valid3)
{
    char response = NULL; //user input

    //checks user input against given valid characters
    //doesn't let response equal an ENTER press
    while(response != valid1 && response != valid2
            && ((valid3 == NULL)? true : response != valid3)
            || response == '\n')
    {
        //print options
        cout << "Please enter only: " << valid1 << " or " << valid2;
        if (valid3 != NULL)
            cout << " or " << valid3;
        cout << endl;

        cin.get(response);

        if(response != '\n')
            CinEmpty();

        if(isalpha(response))
            response = toupper(response);
    }

    cout << endl;

    return response;
}

/******************************************************************************
* Entry: none
*
* Exit: if there is something in the input stream, gets rid of it
*
* Purpose: refreshing input buffer for transitions between cin and getline
*
******************************************************************************/
void CinEmpty()
{
    if(cin.peek() != EOF)
    {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
}
