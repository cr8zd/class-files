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
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cstdio>
#include <climits>
#include <iomanip>

using namespace std;

//prints evenly space characters from a string
void PrintList(string userList);

//prints an alphabetized version of a string
void Alphabetize(string actorAlpha);

//prints the rules of the game
void Rules();

//checks that a response was a number
int NumCheck();

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
           available, //string used to randomize letters for actor
           space; //lines between output
    char letter, //user 2's letter pick
         response; // response to picking from a list ie Y or N
    int length, //number of characters in CHARACTERS
        maxround, //actual max number of rounds for a game
        round, //number of rounds left in a game
        points, //points accumulated in a game
        letPos, //position of picked letter in actor
        buyNum,//number of times user 2 buys a number
        total = 0; //total points over all games played in this session
    bool buy; //true if user 2 buys a number
    bool pointBuy; //true if user 2 buys a number with points not total

    length = CHARACTERS.length();
    space.assign(SCREEN_PUSH, '\n');

    //loop while player wants to play a game
    do
    {
        //clear or reinitialize variable for new game
        int availNum[length]; //stores number in char format
        actor.clear();
        past.clear();
        secret.clear();
        available.clear();
        points = 0;
        maxround = MIN_ROUNDS;
        buyNum = 0;

        available.assign(CHARACTERS);

        //construct actor with random assortment of letter
        //no letter repeats
        while(!available.empty())
        {
            int number;// random number
            srand(time(0));
            number = rand() % available.length();
            actor += available.at(number);
            available.erase(available.begin() + number);
        }

        //construct the array of numbers that represent letters
        //in actor
        for (int i = 0; i < length; i++)
        {
            availNum[i] = i + 1;
        }

        //ask if they want to see the rules
        cout << "Do you want see the rules?" << endl;
        response = ResponseCheck('Y', 'N', NULL);
        if (response == 'Y')
                Rules();

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
            if (isNotLetters)
                cout << "Only letters please." << endl;
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
            string actorAlpha; //alphabetized version of actor

            buy = false;
            pointBuy = false;

            //prints what user thinks secret word is so far, the number of
            // rounds left
            cout << "\nYour guess so far is:\n" << guess
                 << "\n\nYou have " << round << " round"
                 << (round == 1? "" : "s") << " left." << endl;

            //determines if the player can spend points and if they can
            //asks the player what they want to do
            if (total > 4 || points > 0)
            {
                //prints what points they have and what letters are not picked
                cout << "\nYou have " << points << " point"
                     << (points == 1? "" : "s") << " in this game and "
                     << total << " point" << (total == 1? "" : "s")
                     << " in your cache." << endl;
                cout << "\nLetters NOT picked are:\n" << endl;

                actorAlpha = actor;
                Alphabetize(actorAlpha);
                cout << endl;

                cout << "\nDo you want to:"
                     << "\n1) solve the word"
                     << "\n2) buy a letter"
                     << "\n3) pick a number" << endl;
                response = ResponseCheck('1', '2', '3');
                cout << space;

                //user picked solve word, so asks for a word and compare
                //response to secret word
                if (response == '1')
                {
                    string answer; //stores what user thinks secret is

                    cout << "What do you think the secret word is?" << endl;
                    getline(cin, answer);

                    //if answer equals secret, make guess equal secret
                    if (answer.compare(secret) == 0)
                    {
                        guess.assign(secret);
                        round = 0;
                        pointBuy = true;
                    }
                    //answer is wrong so subtract 1 point and round
                    else
                    {
                        cout << "Your guess of " << answer << " was incorrect."
                             << "You lose 1 point and 1 round." << endl;

                        if (points == 0)
                            total--;
                        else
                            points--;

                        round--;
                    }
                }
                //user picked buy a letter
                else if (response == '2')
                {
                    buyNum++;
                    //determines what points to spend on buying a letter
                    if (total > 4 && points != 0) //points in game and cache
                    {
                        cout << "\nDo you want to do?"
                             << "\n1) use 2 points from your cache, and get"
                             << "\n   1 point per letter revealed, or"
                             << "\n2) use 1 point from your current game"
                             << "\n   and not get points for revealed letters."
                             << endl;
                        response = ResponseCheck('1', '2', NULL);

                        if (response == '1') //buy with cache points
                        {
                            pointBuy = false;
                        }
                        else //buy with game points
                        {
                            pointBuy = true;
                        }
                    }

                    //decrease appropriate point(s) and print how many
                    //points remain
                    if (total < 2 || pointBuy) //in game points used
                    {
                        points--;
                        cout << "\nYou used 1 game point and now have "
                             << points << " point" << (points == 1? "" : "s")
                             << " left in this"
                             << " game." << endl;
                        pointBuy = true;
                    }
                    else //total cache points used
                    {
                        total -= 2;
                        cout << "\nYou used 2 points and now have " << total
                             << " point" << (total == 1? "" : "s")
                             << " remaining in your cache." << endl;
                             pointBuy = false;
                    }

                    buy = true;

                    cout << "\nYour guess so far is:\n" << guess << endl;

                    //prints avaiable letters again for user to pick from
                    cout << "\nWhat letter do you want to choose? You can"
                         << "\nchoose from:" << endl;
                    actorAlpha = actor;
                    Alphabetize(actorAlpha);
                    cout << endl;

                    //gets a letter from user and checks it is still active
                    cin.get(letter);
                    CinEmpty();

                    while (actor.find(letter) == string::npos)
                    {
                        cout << "\nYou can only give letters that have not"
                             << "\nbeen picked already. See the list above"
                             << "\nfor your options." << endl;
                        cin.get(letter);
                        CinEmpty();
                    }

                    //store the position of letter and erase that position
                    //in actor
                    letPos = actor.find(letter);
                    actor.erase(actor.begin() + letPos);

                    //shift all numbers after letPos forward 1
                    for (int i = letPos; i < length - (maxround -
                                                       (round - buyNum)); i++)
                    {
                        availNum[i] = availNum[i + 1];
                    }
                }

                //adds letter to past and
                //if it is in secret, adds it to guess
                if (buy)
                {
                    past += letter;

                    for (int i = 0;i < secret.length(); i++)
                    {
                        if (letter == secret.at(i))
                        {
                            guess.at(i) = letter;

                            if (!pointBuy)
                                points++;
                        }
                    }

                    //prints the guess so far
                    cout << "\nYour guess so far is:\n" << guess << endl;
                    buy = false;
                }
            }

            //gets a letter when the user picks a corresponding number
            if (round > 0 && guess.compare(secret) != 0)
            {
                int number; // user input
                int goodNumber; // position of corresponding letter in actor

                //prints past letter picks
                if (!past.empty())
                {
                    cout << "\nLetters that have already been picked are:"
                         << endl;
                    PrintList(past);
                    cout << endl;
                }

                cout << "\nPick an available number listed below" << endl;

                //prints list of available numbers
                for (int i = 0; i < length - (maxround -
                                              (round - buyNum)); i++)
                {

                    cout << left << setw(3) << availNum[i] << " ";

                    if ((i + 1) % 7 == 0)
                        cout << endl;
                }

                cout << endl;
                number = NumCheck();
                bool error = true; // true if number not in availNum

                //checks that number is an available number
                while (error)
                {
                    for (int i = 0; i < length - (maxround - (round - buyNum)); i++)
                    {
                        //confirms that given number is in availNum
                        if (number == availNum[i])
                        {
                            error = false;
                            goodNumber = i;
                        }

                        //number was in availNum so shift all numbers
                        //after forward 1
                        if (!error)
                        {
                            availNum[i] = availNum[i + 1];
                        }
                    }

                    //number wasn't in availNum, so get new number
                    if (error)
                    {
                        cout << "You can only pick from the numbers listed"
                             << " above." << endl;
                        number = NumCheck();
                    }
                }

                letter = actor.at(goodNumber);
                actor.erase(actor.begin() + goodNumber);
                cout << space;
                cout << "\nYou guessed: " << letter << endl;
                round--;
                buy = true;
            }

            bool inWord = false; //letter was in secret word

            if (buy)
            {
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
                cout << "\nYour guess was not in the secret word." << endl;
                inWord = true;
            }

            //guess != secret, so ask for another round
            if (inWord)
            {
                cout << "\nHit enter to play another round." << endl;
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
        total += points;
        cout << "\nYou earned " << points << " point"
             << (points == 1? "" : "s") << " in this game, and"
             << "\nnow have " << total << " point"
             << (total == 1? "" : "s") << " in your cache."
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
* Entry: a string
*
* Exit: for every position i, swap the letter j times while it is less than
*       the proceeding letter
*
* Purpose: printing an alphabetical version of the given string
*
******************************************************************************/
void Alphabetize(string actorAlpha)
{
    for (int i = actorAlpha.length() - 1; i > 0; i--)
    {
        for (int j = actorAlpha.length() - 1; j > 0; j --)
        {
            if (actorAlpha[j] < actorAlpha[j-1])
            {
                char temp; //stores value for swapping

                temp = actorAlpha[j];
                actorAlpha[j] = actorAlpha[j-1];
                actorAlpha[j-1] = temp;
            }
        }
    }

    PrintList(actorAlpha);
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
* Exit: gets user input and checks that it is an int, returns input if it is
*
* Purpose: getting and checking validity of input
*
******************************************************************************/
int NumCheck()
{
    int number; //user input
    string junk; //throws input away if not int
    bool error = false; //input was not an int

    //loops while input is not an int
    do
    {
        cin >> number;

        if (cin.fail() || cin.peek() != '\n')
        {
            cout << "Give only integers please." << endl;
            cin.clear();
            getline(cin, junk);
            error = true;
        }
        else
        {
            error = false;
        }

    } while (error);

    return number;
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

/******************************************************************************
* Entry: none
*
* Exit: prints out the rules of the game
*
* Purpose: takes the massive amount of cout lines out of main
*
******************************************************************************/
void Rules()
{
    cout << "BASIC CONCEPT" << endl;
    cout << "The basic concept of the game is to find the secret word"
         << "\nin as few rounds as possible to earn the most points. If"
         << "\nyou do not find the word in a certain number of rounds,"
         << "\nyou lose."
         << endl;

    cout << "\nGETTING LETTERS" << endl;
    cout << "You can get letters three ways:"
         << "\n1) Randomly pick a letter by hitting enter after a prompt."
         << "\n   In this route you get 1 point for every revealed letter."
         << "\n2) Buy a letter with current game points. Be aware that"
         << "\n   this route means you forfeit any points that any revealed"
         << "\n   letters would give."
         << "\n3) Buy a letter with previous games' points in your cache. In"
         << "\n   this route you still earn 1 point for each revealed letter."
         << "\nBuying a letter happens before a round and you still select"
         << "\na random letter before the round is over."
         << endl;

    cout << "\nGETTING POINTS" << endl;
    cout << "During a game, you get points by finding letters on the"
         << "\nrandom route or buying a letter with 2 points from your"
         << "\ncache, where 1 letter in a word is worth 1 point."
         << "\nAt the end of a game, if you found the word, then you get"
         << "\n1 point for every letter you did not pick. The points you"
         << "\nearn in one game are added to your total points, which"
         << "\ncarry over to subsequent games in a session." << endl;

    cout << "\nSPENDING POINTS" << endl;
    cout << "There are three ways you can spend/lose points in the game."
         << "\n1) Spend 1 point from the current game on a letter."
         << "\n2) Spend 2 points from your total cache on a letter."
         << "\n3) Try to solve the word and fail, losing 1 point."
         << endl;

    cout << "\nWINNING THE GAME" << endl;
    cout << "To win the game, you must either find all of the letters, or"
         << "\nhave at least 1 point and try to solve the word. Be aware"
         << "\nthat if you fail to find the correct word, you will not only"
         << "\nlose 1 point, but also lose a round. No matter if you win"
         << "\nor lose, the points you have remaining in the game will be"
         << "\nadded to your total cache.\n" << endl;

    cout << "\n\n\nHit ENTER when you are ready to begin the game." << endl;
    CinEmpty();
}
