#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace std;

int main()
{
    const int NUMBERS = 10;
    char line[NUMBERS];

    srand(time(0));

    for (int i = 1; i <= NUMBERS; i++)
    {
        cout << rand() << "  ";
        if (i % 5 == 0)
            cout << endl;
    }

    cin.getline(line, NUMBERS);

    return 0;
}
