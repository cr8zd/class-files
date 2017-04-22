/******************************************************************************
* Author: Jennifer Frase
* Date Created: 11/10/14
* Last Modification Date: 11/15/14
* Filename: ticTacToe.cpp
*
* Overview:
* This program will play a given number of games of Tic Tac Toe.
*
* Input:
* The input will be a command line of the number of games of tic tac toe to
* play, as well as sets of two integers that represents the square a player
* wants to place his X or O based on the indexes given in the game.
*
* Output:
* The output for this program will be the board after each round and the
* printing of how many games each player won and the overall winner.
******************************************************************************/

#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

//size of game board
//don't make bigger than 10, size of 3 is for ticTacToe
const int BOARD_SIZE = 3;

//checks if a player has won a game
bool checkWin(char [][BOARD_SIZE]);

//prints the board
void printBoard(char [][BOARD_SIZE]);

int main(int argc, char *argv[])
{
    char board [BOARD_SIZE][BOARD_SIZE]; //game board
    int games; //number of games to play
    int xWins = 0; //number of times X wins
    int oWins = 0; //number of times O wins

    //determine how many games to play
    if (argc > 1)
        games = atoi(argv[1]);
    else
        games = 1;

    if (games < 0)
    {
        cout << "You did not give a valid number of games." << endl;
        return 1;
    }

    //play given number of games
    for (int i = 0; i < games; i++)
    {
        int counter = i; // round number
        bool winner = false; //true if a user wins
        int row, column; // user input for chosen square

        //clear the board
        for (int k = 0; k < BOARD_SIZE; k++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                board[k][j] = '.';
            }
        }

        //play 1 game
        while(!winner && (counter - i) < (BOARD_SIZE * BOARD_SIZE))
        {
            printBoard(board);
            cout << "\nPlayer " << (counter % 2 == 0? "X" : "O")
                 << ": please enter your move." << endl;

            //get player's valid move
            do
            {
                cin >> row >> column;

                if(row > (BOARD_SIZE - 1) || column > (BOARD_SIZE - 1)
                   || row < 0 || column < 0)
                {
                    cout << "\nPlease give a row and column number"
                         << " between 0 and " << (BOARD_SIZE - 1) << " only." << endl;
                }
            }while(row > (BOARD_SIZE - 1) || column > (BOARD_SIZE - 1)
                   || row < 0 || column < 0);

            //check if move is taken
            if (board[row][column] != '.')
            {
                cout << "\nThat space is already taken." << endl;
            }
            else
            {
                board[row][column] = (counter % 2 == 0? 'X' : 'O');
                counter++;
            }

            winner = checkWin(board);
            cout << endl;
        }

        printBoard(board);

        if(winner)
        {
            cout << "\nPlayer " << (counter % 2 == 0? "O" : "X") << " won this game.\n" << endl;
            (counter % 2 == 0? oWins : xWins)++;
        }
    }

    cout << "\nPlayer X won " << xWins << " game" << (xWins == 1? ".":"s.") << endl;
    cout << "Player O won " << oWins << " game" << (oWins == 1? ".\n":"s.\n") << endl;

    if(xWins == oWins)
    {
        cout << "Congratulations to both players, you tied for the most wins."
             << endl;
    }
    else
    {
        cout << "Congratulations to player " << (xWins > oWins? "X" : "O")
             << ", you had the most wins." << endl;
    }

    return 0;
}

/******************************************************************************
* Entry: a single 2D array
*
* Exit: checks if any row, column, or diagonal has all the same character in
*       it, returning true if one does
*
* Purpose: checking the given board for a winner
******************************************************************************/
bool checkWin(char board[][BOARD_SIZE])
{
    int *sums = new int [BOARD_SIZE * 2 + 2]; //array to store sums

    //initialize sums
    for (int i =0; i < BOARD_SIZE * 2 + 2; i++)
    {
        sums[i] = 0;
    }

    //put the sums of values of rows/columns/diagonals in appropriate index
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            sums[i] += board[i][j]; //rows
            sums[j+BOARD_SIZE] += board[i][j]; //columns
            if (i == j)
                sums[BOARD_SIZE *2] += board[i][j]; //backslash diagonal
            if (i + j == BOARD_SIZE - 1)
                sums[BOARD_SIZE * 2 + 1] += board[i][j]; //forward slash diagonal
        }
    }

    //check if any value equals either 3 'X' or 3 'O'
    for (int i = 0; i < BOARD_SIZE * 2 + 2; i ++)
    {
        if (('X' * BOARD_SIZE) == sums[i] || ('O' * BOARD_SIZE) == sums[i])
        {
            delete [] sums;
            sums = 0;
            return true;
        }
    }

    delete [] sums;
    sums = 0;
    return false;
}

/******************************************************************************
* Entry: a single 2D array
*
* Exit: prints the board
*
* Purpose: printing the board
******************************************************************************/
void printBoard(char board[][BOARD_SIZE])
{
    cout << " ";
    //print top index values
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        cout << " " << i;
    }

    cout << endl;

    //print grid and left index values
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        cout << i << " ";
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            cout << left << setw(2) << board[i][j];
        }
        cout << endl;
    }

}
