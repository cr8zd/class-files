#include <iostream>

using namespace std;

const double LPG = .206;

double mpg();

int main()
{
    double pout;
    pout = mpg();
    cout << pout << endl;
    return 0;
}
double mpg()
{
    return LPG;
}

