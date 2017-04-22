/*****************************************************************************************
** Program Filename: gameOfLife.cpp
** Author: Jennifer Frase
** Date: 1/18/15
** Description: play a game of life where the user can set up the board with given
                patterns
** Input: numbers to indicate which patterns and what position to place them, and y or n
          to answer yes or no questions
** Output: the game of life board
*****************************************************************************************/
#include <new>
#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

//#include <windows.h>
#include <unistd.h>

#include <iomanip>
using std::setw;
using std::left;

#include "response_check.h"
#include "int_check.h"

/*use sleep to increment rounds if true, asks for enter press otherwise*/
const bool SLEEPER = false;

/*show all cells' numbers, if true change SCREEN_START to 40 to see
  last 40 columns or change MAX_COLUMNS to 40 to see the first 40 */
const bool ERROR_CHECK = false;

/*creates a new line between each row*/
const bool NEW_LINE = true;

/*# of milliseconds the computer will sleep when SLEEPER is true*/
const int SLEEP_TIME = 260000;

const int MAX_ROWS = 22; //# of visible rows
const int MAX_COLUMNS = 80; //# of visible columns
const int EDGE_SPACE = 100; //# of ghost lines on each edge

/*Change which part of the visible window you see*/
const int SCREEN_START = 0;

/*# of generation until user is asked if they want to continue*/
const int MAX_ROUNDS = 100;

/*print the number of lines to clear screen*/
const int SCREEN_PUSH = 30;

void addBlock(int *, int, int);
void addOscillator(int *, int, int);
void addGlider(int *, int, int);
void addGun(int *, int, int);
void addMirror(int *, int, int);
void addDiamond(int *, int, int);
void addCell(int *, int, int);
void adjust(int *, int, int, int);
void print(int *, char);
void clearBoard(int *);
void setupBoards(int *);

int main()
{

    int firstBoard [(MAX_ROWS + 2*EDGE_SPACE)
            * (MAX_COLUMNS + 2*EDGE_SPACE)] = {0}, // first game board
        secondBoard [(MAX_ROWS + 2*EDGE_SPACE)
            * (MAX_COLUMNS + 2*EDGE_SPACE)] = {0}; // second game board
    int *current, *future; //pointers to current and future boards
    int cell; // value of the current cell of the current game board
    bool emptyBoard; //true if the board empty
    bool staticBoard; //true if the current and future boards will be the same

    setupBoards(firstBoard);

    char response; //user input
    string space; // used to push output off the screen

    space.assign(SCREEN_PUSH, '\n'); //prints space between output

    do
    {
        for(int rounds = 0; rounds < MAX_ROUNDS; rounds++)
        {
            staticBoard = true;
            emptyBoard = true;

            /*change which board is current/future depending on round number*/
            current = (rounds%2 == 0? firstBoard: secondBoard);
            future = (rounds%2 == 0? secondBoard: firstBoard);

            /*print a line above the board*/
            if(NEW_LINE)
            {
                for(int i = 0; i <= MAX_COLUMNS; i++)
                {
                    cout << "_";
                }
                cout << endl;
            }

            /*print the board and change future board before zeroing current board*/
            for(int rows = 0; rows < MAX_ROWS + 2*EDGE_SPACE; rows++)
            {
                /* print a line before each visible row*/
                if(NEW_LINE  && rows >= EDGE_SPACE && rows < MAX_ROWS + EDGE_SPACE)
                    cout << "|";

                for(int columns = 0; columns < MAX_COLUMNS + 2*EDGE_SPACE; columns++)
                {
                    cell = current[columns + rows*(MAX_COLUMNS + 2*EDGE_SPACE)];

                    /*determine if the cell is visible*/
                    if (columns >= EDGE_SPACE + SCREEN_START && rows >= EDGE_SPACE
                        && columns < MAX_COLUMNS + EDGE_SPACE
                        && rows < MAX_ROWS + EDGE_SPACE)
                    {
                        /*print numbers if error checking, otherwise print symbols*/
                        if(ERROR_CHECK)
                            cout << left << setw(2) << cell;
                        else
                            cout << (cell/10 == 0? ' ' : 'O');

                        /*print a line after each row before ending the line*/
                        if(NEW_LINE && columns == MAX_COLUMNS + EDGE_SPACE - 1)
                            cout << "|" << endl;

                        /*determine if board is not empty nor static*/
                        if(cell/10 == 1)
                            emptyBoard = false;
                        if(cell == 3 || (cell/10 == 1 && (cell != 13 && cell != 12)))
                            staticBoard = false;
                    }

                    /*if cell is dying or being born, adjust the cell and neighbors*/
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

                    /*add value to future board and zero out the current board*/
                    future[columns + rows*(MAX_COLUMNS + 2*EDGE_SPACE)] += cell;
                    current[columns + rows*(MAX_COLUMNS + 2*EDGE_SPACE)] = 0;
                }
            }

            /*print a line below the board*/
            if(NEW_LINE)
            {
                for(int i = 0; i <= MAX_COLUMNS; i++)
                {
                    cout << "_";
                }
                cout << endl;
            }

            /*if the boards will not change break*/
            if(emptyBoard || staticBoard)
                break;

            if(rounds + 1 < MAX_ROUNDS)
            {
                if(SLEEPER)
                    usleep(SLEEP_TIME);
                else
                {
                    cout << "\nHit ENTER to go next generation." << endl;
                    cin.get();
                }
                cout << space;
            }
        }

        /*if boards will not change, print appropriate message and quit*/
        if(emptyBoard)
        {
            cout << "\nThe board has no live cells, and so cannot continue." << endl;
            break;
        }
        if(staticBoard)
        {
            cout << "\nThe board is static and will no longer change." << endl;
            break;
        }


        cout << "\nDo you want to continue the game for another "
             << MAX_ROUNDS << " rounds." << endl;

    }while( responseCheck('Y', 'N', '\0', '\0') == 'Y');

    return 0;
}

/*****************************************************************************************
** Function: addBlock
** Description: creates a static pattern
** Parameters:  a pointer to game board, and two ints: row and column numbers of a cell
** Pre-Conditions: row and column must be valid numbers for the board given
** Post-Conditions: none
*****************************************************************************************/
void addBlock(int *current, int row, int column)
{
    addCell(current, row, column);
    addCell(current, row + 1, column);
    addCell(current, row, column + 1);
    addCell(current, row + 1, column + 1);
}

/*****************************************************************************************
** Function: addOscillator
** Description: creates a pattern which switches between vertical and horizontal
** Parameters:  a pointer to game board, and two ints: row and column numbers of a cell
** Pre-Conditions: row and column must be valid numbers for the board given
** Post-Conditions: none
*****************************************************************************************/
void addOscillator(int *current, int row, int column)
{
    addCell(current, row, column + 1);
    addCell(current, row, column);
    addCell(current, row, column + 2);
}

/*****************************************************************************************
** Function: addGlider
** Description: creates a pattern which travels north west
** Parameters:  a pointer to game board, and two ints: row and column numbers of a cell
** Pre-Conditions: row and column must be valid numbers for the board given
** Post-Conditions: none
*****************************************************************************************/
void addGlider(int *current, int row, int column)
{
    addOscillator(current, row, column);
    addCell(current, row + 1, column);
    addCell(current, row + 2, column + 1);
}

/*****************************************************************************************
** Function: addGun
** Description: creates a pattern which creates gliders that travel south east
** Parameters:  a pointer to game board, and two ints: row and column numbers of a cell
** Pre-Conditions: row and column must be valid numbers for the board given
** Post-Conditions: none
*****************************************************************************************/
void addGun( int *current, int row, int column)
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

/*****************************************************************************************
** Function: addMirror
** Description: creates a pattern which expands in a mirror image
** Parameters:  a pointer to game board, and two ints: row and column numbers of a cell
** Pre-Conditions: row and column must be valid numbers for the board given
** Post-Conditions: none
*****************************************************************************************/
void addMirror(int *current, int row, int column)
{
    addCell(current, row, column + 1);
    addCell(current, row, column + 3);
    addCell(current, row + 1, column);
	addCell(current, row + 1, column + 2);
	addCell(current, row + 1, column + 3);
	addOscillator(current, row + 2, column);
	addCell(current, row + 2, column + 3);
	addOscillator(current, row + 5, column);
	addCell(current, row + 5, column + 3);
	addCell(current, row + 6, column);
	addCell(current, row + 6, column + 2);
	addCell(current,row + 6, column + 3);
	addCell(current, row + 7, column + 1);
	addCell(current, row + 7, column + 3);
}

/*****************************************************************************************
** Function: addDiamond
** Description: creates a pattern which expands until it stabilizes into a static pattern
** Parameters:  a pointer to game board, and two ints: row and column numbers of a cell
** Pre-Conditions: row and column must be valid numbers for the board given
** Post-Conditions: none
*****************************************************************************************/
void addDiamond(int *current, int row, int column)
{
	addOscillator(current, row, column + 1);
	addCell(current, row + 1, column);
	addCell(current, row + 1, column + 4);
	addCell(current, row + 2, column + 1);
	addCell(current, row + 2, column + 3);
	addCell(current, row + 3, column + 2);
}

/*****************************************************************************************
** Function: addCell
** Description: Makes a given cell alive and adjusts the board
** Parameters:  a pointer to game board, and two ints: row and column numbers of a cell
** Pre-Conditions: row and column must be valid numbers for the board given
** Post-Conditions: none
*****************************************************************************************/
void addCell(int *current, int row, int column)
{
    current[column + row*(MAX_COLUMNS + 2*EDGE_SPACE)] += 10;
    adjust(current, row, column, 1);
}

/*****************************************************************************************
** Function: adjust
** Description: Takes a given cell and adds the addValue to all cells around it
** Parameters:  a pointer to game board, and three ints: row and column numbers of a cell
                and the value that will be added to surrounding cells
** Pre-Conditions: row and column numbers must be valid for the given board
** Post-Conditions: none
*****************************************************************************************/
void adjust(int *future, int row, int column, int addValue)
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

/*****************************************************************************************
** Function: print
** Description: prints out the given board where the non living cells are represented
                with the given value
** Parameters:  a pointer to game board, and a char to represent dead cells
** Pre-Conditions: none
** Post-Conditions: none
*****************************************************************************************/
void print(int *current, char emptySymbol)
{
    /*print a line below the board*/
    if(NEW_LINE)
    {
        for(int i = 0; i <= MAX_COLUMNS; i++)
        {
            cout << "_";
        }
        cout << endl;
    }

    /*print the board using numbers or symbols*/
    for(int rows = 0; rows < MAX_ROWS + 2*EDGE_SPACE; rows++)
    {
        /* print a line before each visible row*/
        if(NEW_LINE  && rows >= EDGE_SPACE && rows < MAX_ROWS + EDGE_SPACE)
            cout << "|";
        for(int columns = 0; columns < MAX_COLUMNS + 2*EDGE_SPACE; columns++)
        {
            int cell = current[columns + rows*(MAX_COLUMNS + 2*EDGE_SPACE)];

            if (columns >= EDGE_SPACE + SCREEN_START && rows >= EDGE_SPACE
                && columns < MAX_COLUMNS + EDGE_SPACE
                && rows < MAX_ROWS + EDGE_SPACE)
            {
                if(ERROR_CHECK)
                    cout << left << setw(2) << cell;
                else
                    cout << (cell/10 == 0? emptySymbol : 'O');

                /*print a line after each row*/
                if(NEW_LINE && columns == MAX_COLUMNS + EDGE_SPACE - 1)
                    cout << "|" << endl;
            }
        }
    }
    /*print a line below the board*/
    if(NEW_LINE)
    {
        for(int i = 0; i <= MAX_COLUMNS; i++)
        {
            cout << "-";
        }
        cout << endl;
    }
}

/*****************************************************************************************
** Function:clearBoard
** Description: Changes all cells in the given range back to 0
** Parameters:  a pointer to game board, and 4 integers: a starting row and column and an
                ending row and column
** Pre-Conditions: all integers must be in the possible range for the given board
                   row and column are the row number of the top most alive cell and the
                   column number of the left most alive cell
** Post-Conditions: none
*****************************************************************************************/
void clearBoard(int *current, int row, int column, int rowNum, int colNum)
{
    for(int i = -1; i <= rowNum; i++)
    {
        for(int j = -1; j <= colNum; j++)
        {
            current[column + j + (row + i)*(MAX_COLUMNS + 2*EDGE_SPACE)] = 0;
        }
    }
}

/*****************************************************************************************
** Function:setUpBoards
** Description: Asks the user what patterns they want to add and where they want to add
                it. If that spot is available (won't interfere with other patterns), then
                the pattern is added to firstBoard, and the entire rectangle is added to
                availBoard. Repeats until user doesn't want to add more patterns.
** Parameters:  a pointer to game board, firstBoard
** Pre-Conditions: all values in firstBoard must be 0
** Post-Conditions: none
*****************************************************************************************/
void setupBoards(int *firstBoard)
{
    int availBoard [(MAX_ROWS + 2*EDGE_SPACE) * (MAX_COLUMNS + 2*EDGE_SPACE)] = {0};

    /*add a pattern to the board, repeat until the user doesn't want to add anymore*/
    do
    {
        int row, column,
            rowNum, colNum;
        char pattern, response;

        /*ask for a pattern*/
        cout << "Please choose a pattern to add\n";
        cout << "1) BLOCK (2x2)\n"
             << "2) SIMPLE OSCILLATOR (1x3)\n"
             << "3) GLIDER (3x3)\n"
             << "4) GLIDER GUN (9x36)" << endl;
        pattern = responseCheck('1', '2', '3', '4');

        /*try to add the patten to the board*/
        do
        {
            bool there = false;

            cout << "\nCURRENT BOARD:" << endl;
            print(availBoard, '.');

            cout << "\n\nWhere do you want to place the top left corner of the pattern?"
                 << endl;

            /*determine the rectangle size for the selected pattern*/
            if(pattern == '1')
            {
                rowNum = 2;
                colNum = 2;
            }
            else if(pattern == '2')
            {
                rowNum = 1;
                colNum = 3;
            }
            else if(pattern == '3')
            {
                rowNum = 3;
                colNum = 3;
            }
            else if(pattern == '4')
            {
                rowNum = 9;
                colNum = 36;
            }

            /*ask for a placement, which is constricted so that the whole pattern is
              on the board*/
            cout << "Row #: ";
            row = intCheck(1, 22 - rowNum + 1) + EDGE_SPACE - 1;
            cout << "\nColumn #: ";
            column = intCheck(1, 80 - colNum + 1) + EDGE_SPACE - 1;

            /*Determine if any corners of the rectangle overlap with already placed
              patterns*/
            if(availBoard[column + row*(MAX_COLUMNS + 2*EDGE_SPACE)] != 0
               || availBoard[column + colNum + row*(MAX_COLUMNS + 2*EDGE_SPACE)] != 0
               || availBoard[column + (row + rowNum)*(MAX_COLUMNS + 2*EDGE_SPACE)] != 0
               || availBoard[column + colNum
                    + (row + rowNum)*(MAX_COLUMNS + 2*EDGE_SPACE)] != 0)
                there = true;

            /*if the pattern overlap, state so, otherwise add it*/
            if(there)
                cout << "\nThat spot is occupied" << endl;
            else
            {
                if(pattern == '1')
                    addBlock(firstBoard, row, column);
                else if(pattern == '2')
                    addOscillator(firstBoard, row, column);
                else if(pattern == '3')
                    addGlider(firstBoard, row, column);
                else if(pattern == '4')
                    addGun(firstBoard, row, column);

                /*add pattern's rectangle to availBoard*/
                for(int i = -1; i <= rowNum; i++)
                {
                    for(int j = -1; j <= colNum; j++)
                    {
                        addCell(availBoard, i + row, j + column);
                    }
                }
            }

            cout << "The board now looks like:" << endl;
            print(firstBoard, ' ');

            cout << "\nDo you want to pick different spot?" << endl;
            response = responseCheck('Y', 'N', '\0', '\0');

            /*if the user want to choose another spot for a pattern that was
              added, clear the spot where it was added*/
            if(!there && response == 'Y')
            {
                clearBoard(availBoard, row, column, rowNum, colNum);
                clearBoard(firstBoard, row, column, rowNum, colNum);
            }

        }while(response == 'Y');

        cout << "Do you want to pick another pattern to place?" << endl;

    }while(responseCheck('Y', 'N', '\0', '\0') == 'Y');
}
