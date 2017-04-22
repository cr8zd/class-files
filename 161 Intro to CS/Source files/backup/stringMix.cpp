#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

void strMix(char phrase[], char phraseMix[]);

int main()
{
    const int arraySize = 30;
    char phrase[arraySize],
         phraseMix[arraySize];
    cout << "Please give me a phrase." << endl;
    cin.getline(phrase, arraySize);
    strMix(phrase, phraseMix);
    cout << phrase << endl;
    cout << phraseMix << endl;
    return 0;
}

void strMix(char phrase[], char phraseMix[])
{
    int length = strlen(phrase);
    int numbers[length];

    //loop once per character in phrase
    for(int i = 0; i < length; i++)
    {
        bool there;
        //check that number isn't in numbers
        do
        {
            srand(time(0));
            int number = rand() % length;
            there = false;
            //check every element of numbers to see if number
            //is in numbers
            for (int j = 0; j < i; j++)
            {
                if (numbers[j] == number)
                    there = true;
            }
            //if number isn't in numbers, then add number to numbers and add
            //the letter at the position of number in phrase to the end of phraseMix
            if (!there)
            {
                numbers[i] = number;
                phraseMix[number] = phrase[i];
            }
        }while (there);

    }
}
