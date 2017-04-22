#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <string.h>
#include <cstdio>
#include <climits>
#include <iomanip>
#include <cmath>

using namespace std;

void rules();
int numCheck(int range);
char responseCheck(char valid1, char valid2, char valid3);
void cinEmpty();

int main()
{
    const int MIN_ROUNDS = 10;
    const int MAX_ROUNDS = 15;
    const int SCREEN_PUSH = 50;
    const char PLACE_HOLD = '?';
    const string CHARACTERS = "abcdefghijklmnopqrstuvwxyz";
    string secret,
           guess,
           past,
           missing,
           actor,
           available;
    char letter,
         response;
    int length = CHARACTERS.length(),
        maxround,
        round,
        points,
        letPos,
        buyNum,
        total = 0;
    bool buy;
    bool pointBuy;

    do
    {
        char availNum [length] [2];
        actor.clear();
        past.clear();
        missing.clear();
        secret.clear();
        available.clear();
        points = 0;
        maxround = MIN_ROUNDS;
        buyNum = 0;

        available.assign(CHARACTERS);

        //construct actor
        while(!available.empty())
        {
            int number;
            srand(time(0));
            number = rand() % available.length();
            actor += available.at(number);
            available.erase(available.begin() + number);
        }

        for (int i = 0; i < length; i++)
        {
            char currentNum[10];
            itoa(i, currentNum, 10);
            for (int j = 0; j < strlen(currentNum); j++)
            {
                availNum [i] [j] = currentNum[j];
            }
        }

        //ask if they want to see the rules
        cout << "Do you want see the rules?" << endl;
        response = responseCheck('Y', 'N', NULL);
        if (response == 'Y')
                rules();

        cout << "Please give me a secret word." << endl;
        while(secret.empty())
        {
            getline(cin, secret);
        }
        for(int i = 0; i < secret.length(); i++)
        {
            tolower(secret.at(i));
        }
        if (secret.length() / 2 > MIN_ROUNDS)
            maxround = secret.length() / 2;
        if (maxround > MAX_ROUNDS)
            maxround = MAX_ROUNDS;
        guess.assign(secret.length(), PLACE_HOLD);
        round = maxround;

        string space;
		space.assign(SCREEN_PUSH, '\n');
		cout << space;

        while (round > 0 && guess.compare(secret) != 0)
        {
            buy = false;
            pointBuy = false;
            cout << "\nYour guess so far is:\n" << guess
                 << "\nYou have " << round << " round" << (round == 1? "" : "s")
                 << " left." << endl;
            if (!past.empty())
            {
                cout << "\nLetters that have already been picked are:" << endl;
                for(int i = 0; i < past.length(); i++)
                {
                    cout << left << setw(4) << past.at(i);
                    if ((i + 1) % 7 == 0)
                        cout << endl;
                }
                cout << endl;
            }
            if (total > 4 || points > 0)
            {
                cout << "\nYou have " << points << " point" << (points == 1? "" : "s")
                     << " in this game and " << total << " point"
                     << (total == 1? "" : "s") << " in your cache." << endl;
                cout << "\nDo you want to:"
                     << "\n1) solve the word"
                     << "\n2) buy a letter"
                     << "\n3) neither?" << endl;
                response = responseCheck('1', '2', '3');
                cout << space;
                if (response == '1')
                {
                    string answer;
                    cout << "What do you think the secret word is?" << endl;
                    getline(cin, answer);
                    if (answer.compare(secret) == 0)
                    {
                        guess.assign(secret);
                        round = 0;
                        pointBuy = true;
                    }
                    else
                    {
                        cout << "Your guess of " << answer << " was incorrect. You lose"
                             << " 1 point and 1 round." << endl;
                        if (points == 0)
                            total--;
                        else
                            points--;
                        round--;
                    }
                }
                else if (response == '2')
                {
                    buyNum++;
                    if (total > 4 && points != 0)
                    {
                        cout << "\nDo you want to do?"
                             << "\n1) use 5 points from your cache, and get"
                             << "\n   1 point per letter revealed, or"
                             << "\n2) use 1 point from your current game"
                             << "\n   and not get points for revealed letters."
                             << endl;
                        response = responseCheck('1', '2', NULL);
                        if (response == '1')
                        {
                            total -= 5;
                            cout << "\nYou used 5 points and now have " << total
                                 << " point" << (total == 1? "" : "s") << " remaining"
                                 << " in your cache." << endl;
                        }
                        else
                        {
                            points--;
                            cout << "\nYou used 1 game point and now have " << points
                                 << " point" << (points == 1? "" : "s") << "left in this"
                                 << "game." << endl;
                            pointBuy = true;
                        }
                    }
                    else if (total < 5)
                    {
                        points--;
                        cout << "\nYou used 1 game point and now have " << points
                             << " point" << (points == 1? "" : "s") << "left in this"
                             << "game." << endl;
                        pointBuy = true;
                    }
                    else
                    {
                        total -= 5;
                        cout << "\nYou used 5 points and now have " << total
                             << " point" << (total == 1? "" : "s") << " remaining"
                             << " in your cache." << endl;
                    }
                    buy = true;
                    cout << "\nWhat letter do you want to choose? You can"
                         << "\nchoose from:" << endl;
                    string actorAlpha = actor;
                    for (int i = actorAlpha.length() - 1; i > 0; i--)
                    {
                        for (int j = actorAlpha.length() - 1; j > 0; j --)
                        {
                            if (actorAlpha[j] < actorAlpha[j-1])
                            {
                                char temp;
                                temp = actorAlpha[j];
                                actorAlpha[j] = actorAlpha[j-1];
                                actorAlpha[j-1] = temp;
                            }
                        }
                    }

                    for (int i = 0; i < actorAlpha.length(); i++)
                    {
                        cout << left << setw(3) << actorAlpha.at(i) << " ";
                        if ((i + 1) % 7 == 0 && i != actorAlpha.length() - 1)
                            cout << endl;
                    }
                    cout << endl;
                    cin.get(letter);
                    cinEmpty();
                    while (actor.find(letter) == string::npos)
                    {
                        cout << "\nYou can only give letters that have not been"
                             << "\npicked already. See the list above for your"
                             << "\noptions." << endl;
                        cin.get(letter);
                        cinEmpty();
                    }
                    letPos = actor.find(letter);
                    actor.erase(actor.begin() + actor.find(letter));
                    for (int i = letPos; i < length - (maxround - (round - buyNum)); i++)
                    {
                        for (int j = 0; j < 2; j++)
                        {
                            availNum [i] [j] = availNum [i+1] [j];
                        }
                    }
                }
                if (buy)
                {
                    cout << "\nYou guessed: " << letter << endl;
                    cout << "\nHit enter to continue." << endl;
                    cinEmpty();
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
                    buy = false;
                }
            }
            if (!buy && round > 0 && guess.compare(secret) != 0)
            {
                int number;
                int goodNumber;
                cout << "\nPick an available number listed below" << endl;
                for (int i = 0; i < length - (maxround - (round - buyNum)); i++)
                {
                    char currentNum[2];
                    for (int j = 0; j < 2 ; j++)
                    {
                        currentNum[j] = availNum [i] [j];
                    }
                    cout << left << setw(3) << atoi(currentNum) + 1 << " ";
                    if ((i + 1) % 7 == 0)
                        cout << endl;
                }
                cout << endl;
                number = numCheck(length);
                bool error = true;
                while (error)
                {
                    for (int i = 0; i < length - (maxround - (round - buyNum)); i++)
                    {
                        int currentNumber;
                        char currentNum[3];
                        for (int j = 0; j < 2 ; j++)
                        {
                            currentNum[j] = availNum [i] [j];
                        }
                        currentNumber = atoi(currentNum);
                        if (number == currentNumber+1)
                        {
                            error = false;
                            goodNumber = i;
                        }
                        if (!error)
                        {
                            for (int j = 0; j < 2; j++)
                            {
                                availNum [i] [j] = availNum [i+1] [j];
                            }
                        }
                    }
                    if (error)
                    {
                        cout << "You can only pick from the numbers listed above." << endl;
                        number = numCheck(length);
                    }
                }
                letter = actor.at(goodNumber);
                actor.erase(actor.begin() + goodNumber);
                round--;
                buy = true;
            }
            if (buy)
            {
                cout << "\nYou guessed: " << letter << endl;
                cout << "\nHit enter to play another round." << endl;
                cinEmpty();
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
            }

            cout << space;

            if(round <= maxround/2 && points == 0 && guess.compare(secret) != 0)
            {
                cout << "Here is a point, I suggest buying a letter before the next"
                     << "\nround, as you get letters per round then. However if you"
                     << "\nkeep it, it will carry over to the next game." << endl;
                points++;
            }

        }

        cout << "\nThe secret word was " << secret << endl;
        for(int i = 0; i < guess.length(); i++)
        {
            char missed = NULL;
            if (guess.at(i) == PLACE_HOLD)
                missed = secret.at(i);
            if (missed != NULL)
            {
                if (missing.find(missed) == string::npos)
                    missing += missed;
            }
        }
        if (guess == secret)
        {
            cout << "\nCongratulations, you found the secret word!"
                 << "\nYou get " << actor.length() << " extra point"
                 << (actor.length() == 1? "" : "s") << " remaining"
                 << endl;
            points += actor.length();
        }
        else if (round = maxround)
        {
            cout << "\nYou lost. You still needed to find:" << endl;
            for(int i = 0; i < missing.length(); i++)
            {
                cout << missing.at(i) << " ";
                if ((i + 1) % 7 == 0)
                    cout << endl;
            }
        }
        total += points;
        cout << "\nYou earned " << points << " point"
             << (points == 1? "" : "s") << " in this game, and"
             << "\nnow have " << total << " point"
             << (total == 1? "" : "s") << " in your cache."
             << endl;
        cout << "\nDo you want to play again?" << endl;
        response = responseCheck('Y', 'N', NULL);
        cout << space;

    }while (toupper(response) != 'N');

    return 0;
}

char responseCheck(char valid1, char valid2, char valid3)
{
    char response = NULL;
    while(response != valid1 && response != valid2
            && ((valid3 == NULL)? response == NULL : response != valid3)
            || response == '\n')
    {
        cout << "Please enter only: " << valid1 << " or " << valid2;
        if (valid3 != NULL)
            cout << " or " << valid3;
        cout << endl;
        cin.get(response);
        cinEmpty();
        if(isalpha(response))
            response = toupper(response);
    }
    cout << endl;
    return response;
}

int numCheck(int range)
{
    int number;
    bool error = false;
    cin >> number;
    cinEmpty();
    do
    {
        if (error)
        {
            cin >> number;
            error = false;
        }
        if (cin.fail())
        {
            error = true;
        }
    } while (error);

    return number;
}

void cinEmpty()
{
    if(cin.peek() != EOF)
    {
        cin.ignore();
        cin.clear();
    }
}

void rules()
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
         << "\nrandom route or buying a letter with 5 points from your"
         << "\ncache, where 1 letter in a word is worth 1 point."
         << "\nIf you are unlucky enough to be past half way through your rounds"
         << "\nwithout having any points, you will be given 1 point."
         << "\nAt the end of a game, if you found the word, then you get"
         << "\n1 point for every letter you did not pick. The points you"
         << "\nearn in one game is added to your total points, which"
         << "\ncarry over to subsequent games." << endl;
    cout << "\nSPENDING POINTS" << endl;
    cout << "There are three ways you can spend/lose points in the game."
         << "\n1) Spend 1 point from the current game on a letter."
         << "\n2) Spend 5 points from your total cache on a letter."
         << "\n3) Try to solve the word and fail, spending 1 point."
         << endl;
    cout << "\nWINNING THE GAME" << endl;
    cout << "To win the game, you must either find all of the letters, or"
         << "\nhave at least 1 point and try to solve the word. Be aware"
         << "\nthat if you fail to find the correct word, you will not only"
         << "\nlose 1 point, but also lose a round. No matter if you win"
         << "\nor lose, the points you gain in the game will be added to your"
         << "\ntotal amount.\n" << endl;
    cout << "\n\n\nHit ENTER when you are ready to begin the game." << endl;
    cinEmpty();
}
