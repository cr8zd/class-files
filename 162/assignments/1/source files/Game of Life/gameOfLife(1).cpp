/*****************************************************************************************

*****************************************************************************************/
#include <new>
#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <windows.h>
#include <unistd.h>

#include <cstdio>
using std::setw;
using std::left;

#include "response_check.h"

const int SECONDS = 260;
const int MAX_ROWS = 22;
const int MAX_COLUMNS = 80;
const int EDGE_SPACE = 50;
const int MAX_ROUNDS = 100;
const int SCREEN_PUSH = 25; //print the number of lines to clear screen

void addOscillator(int [] , int, int);

void addGlider(int [], int, int);

void addGun( int current [], int row, int column);

void addCell(int current [], int row, int column);

void adjust(int [], int, int, int);

int main()
{
    int firstBoard [(MAX_ROWS + 2*EDGE_SPACE) * (MAX_COLUMNS + 2*EDGE_SPACE)] = {0},
        secondBoard [(MAX_ROWS + 2*EDGE_SPACE) * (MAX_COLUMNS + 2*EDGE_SPACE)] = {0};
    int *current, *future;
    int cell;
    addOscillator(firstBoard, 18 + EDGE_SPACE, 10 + EDGE_SPACE);
    addGlider(firstBoard, 10 + EDGE_SPACE, 50 + EDGE_SPACE);
    addGun(firstBoard, 1 + EDGE_SPACE, 1 + EDGE_SPACE);
    char response; //user input
    string space; // used to push output off the screen

    space.assign(SCREEN_PUSH, '\n');

    do
    {
        for(int rounds = 0; rounds < MAX_ROUNDS; rounds++)
        {
            current = (rounds%2 == 0? firstBoard: secondBoard);
            future = (rounds%2 == 0? secondBoard: firstBoard);
            for(int rows = 0; rows < MAX_ROWS + 2*EDGE_SPACE; rows++)
            {
                for(int columns = 0; columns < MAX_COLUMNS + 2*EDGE_SPACE; columns++)
                {
                        cell = current[columns + rows*(MAX_COLUMNS + 2*EDGE_SPACE)];
                        if (columns >= EDGE_SPACE && rows >= EDGE_SPACE
                            && columns < MAX_COLUMNS + EDGE_SPACE
                            && rows < MAX_ROWS + EDGE_SPACE)
                        {
                            cout << left << setw(3) << cell;//(cell/10 == 0? ' ' : 'O'); //left << setw(3) << cell;//
                            //if(columns == MAX_COLUMNS + EDGE_SPACE - 1)
                              //  cout << endl;
                        }

                        if (cell/10 == 1 && cell != 13 && cell != 12)
                        {
                            cell -= 10;
                            adjust(future, rows, columns, -1);
                        }
                        else if (cell == 3)
                        {
                            cell += 10;
                            adjust(future, rows, columns, 1);
                        }
                        future[columns + rows*(MAX_COLUMNS + 2*EDGE_SPACE)] += cell;
                        current[columns + rows*(MAX_COLUMNS + 2*EDGE_SPACE)] = 0;
                }
            }
            if(rounds + 1 < MAX_ROUNDS)
            {
                Sleep(SECONDS);
                //cout << "\nHit ENTER to go next generation." << endl;
                //cin.get();
                //cout << space;
            }
        }

        cout << "\nDo you want to continue the game for another "
             << MAX_ROUNDS << " rounds." << endl;
    }while( responseCheck('Y', 'N', '\0', '\0') == 'Y');
    return 0;
}

void addBlock(int current[], int row, int column)
{
    addCell(current, row, column);
    addCell(current, row + 1, column);
    addCell(current, row, column + 1);
    addCell(current, row + 1, column + 1);
}

void addOscillator(int current[] , int row, int column)
{
    addCell(current, row, column + 1);
    addCell(current, row, column);
    addCell(current, row, column + 2);
}

void addGlider(int current[], int row, int column)
{
    addOscillator(current, row, column);
    addCell(current, row + 1, column);
    addCell(current, row + 2, column + 1);
}

void addGun( int current [], int row, int column)
{
    addBlock(current, row + 4, column);
    addCell(current, row + 2, column + 12);
    addCell(current, row + 2, column + 13);
    addCell(current, row + 3, column + 11);
    addCell(current, row + 4, column + 10);
    addCell(current, row + 5, column + 10);
    addCell(current, row + 6, column + 10);
    addCell(current, row + 7, column + 11);
    addCell(current, row + 8, column + 12);
    addCell(current, row + 8, column + 13);
    addCell(current, row + 7, column + 15);
    addCell(current, row + 6, column + 16);
    addCell(current, row + 5, column + 14);
    addCell(current, row + 5, column + 16);
    addCell(current, row + 5, column + 17);
    addCell(current, row + 4, column + 16);
    addCell(current, row + 3, column + 15);
    addCell(current, row + 2, column + 20);
    addCell(current, row + 3, column + 20);
    addCell(current, row + 4, column + 20);
    addCell(current, row + 2, column + 21);
    addCell(current, row + 3, column + 21);
    addCell(current, row + 4, column + 21);
    addCell(current, row + 1, column + 22);
    addCell(current, row + 5, column + 22);
    addCell(current, row, column + 24);
    addCell(current, row + 1, column + 24);
    addCell(current, row + 5, column + 24);
    addCell(current, row + 6, column + 24);
    addBlock(current, row + 2, column + 34);
}

void addCell(int current [], int row, int column)
{
    current[column + row*(MAX_COLUMNS + 2*EDGE_SPACE)] += 10;
    adjust(current, row, column, 1);
}

void adjust(int future[] , int row, int column, int addValue)
{
    for(int curRow = row - 1; curRow < row + 2; curRow++)
    {
        for(int curCol = column - 1; curCol < column + 2; curCol++)
        {
            if(curRow != row || curCol != column)
                future[curCol + curRow*(MAX_COLUMNS + 2*EDGE_SPACE)] += addValue;
        }
    }
}
