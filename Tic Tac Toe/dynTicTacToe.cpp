// dynTicTacToe.cpp (uses dynamic board allocation)
//
// Created by Shaanan Curtis on 3/5/18.
// Copyright © 2018 SEC. All rights reserved.
//
/*
    This program uses dynamic allocation to create a board
    in which a participant can control the size of the playing field.
    It then proceeds to perform a user-oriented game of Tic Tac Toe.
*/

#include <cstdlib>                 // system definitions
#include <iostream>                // I/O definitions
#include <iomanip>
#include <cctype>
using namespace std;               // make std:: accessible

/**********************************************************************************************************/

// VARIABLE INITIALIZATION & ASSIGNMENT //

/*========================================================================================================*/

// PLAYERS
const int X = 1, O = -1, EMPTY = 0;         // assigns values to the possible marks (computer sees numbers)
int currentPlayer;                          // current player (X or O)

// PLAYING BOARD
int** board;                                // playing board allocation (2D matrix: square board)
int dimensions;                             // board dimensions (rows x cols) | assumes rows = cols
int counter;                                // number of available moves

/**********************************************************************************************************/

// FUNCTION DEFINITIONS //

/*========================================================================================================*/

//----------------------------------------
// clearBoard (function)
//
// • clears playing board
// • assigns every cell to EMPTY
// • resets currentPlayer to X
//
// Params: none
// I/O: none
// Return: void (nothing)
//-----------------------------------------
void clearBoard()                           // clear the board
{
    for (int i = 0; i < dimensions; i++)
    {
        for (int j = 0; j < dimensions; j++)
        {
            board[i][j] = EMPTY;            // empty every cell
        }
    }
    currentPlayer = X;                      // player X starts
}




//----------------------------------------
// putMark (function)
//
// • places mark in specified coordinate
// • switches players
// • decrements number of available moves
//
// Params: 2 integers
// I/O: none
// Return: void (nothing)
//-----------------------------------------
void putMark(int x, int y)                  // put mark in row i column j
{
    board[x][y] = currentPlayer;            // mark with current player first
    currentPlayer = -currentPlayer;         // switch players
    counter--;
}




//-----------------------------------------------------------------
// isWin (function)
//
// • checks all possibilities
// • assumes responsibility on programmer when determining a match
// • returns true or false
//
// Params: int mark (each player is assigned a mark)
// I/O: none
// Return: bool
//-----------------------------------------------------------------
bool isWin(int mark)
{
    int win = dimensions*mark;                                      // +n for X and -n for O
    int sum = 0, row[dimensions], col[dimensions], d1, d2;

    //horizontal
    for(int x=0; x<dimensions; x++)
    {
        for(int y=0; y<dimensions; y++)
        {
            sum = sum + board[x][y];
        }
        row[x] = sum;
        sum = 0;
    }
    
    //vertical
    for(int y=0; y<dimensions; y++)
    {
        for(int x=0; x<dimensions; x++)
        {
            sum = sum + board[x][y];
        }
        col[y] = sum;
        sum = 0;
    }
    
    //diagnol 1
    int j=0;
    for(int i=0; i<dimensions; i++)
    {
        sum = sum + board[i][j];
        j++;
    }
    d1 = sum;
    sum = 0;
    
    //diagnol 2
    j=0;
    for(int i=(dimensions-1); i>=0; i--)
    {
        sum = sum + board[i][j];
        j++;
    }
    d2 = sum;
    
    //check if a match was successfully found (only one should exist)
    for(int i=0; i<dimensions; i++)
    {
        if(row[i]==win || col[i]==win || d1==win || d2==win)
        {
            return true;
        }
    }
    
    return false;
}




//---------------------------------------------------------
// getWinner (function)
//
// • determines a winner out of 2 players
// • if no winner is found, assumes further responsibility
//    on programmer and returns EMPTY
//
// Params: none
// I/O: none
// Return: int
//---------------------------------------------------------
int getWinner()                                             // who wins?
{
    if (isWin(X))
    {return X;}
    else if (isWin(O))
    {return O;}
    else
    return EMPTY;
}




//-------------------------------------------------------
// printBoard (function)
//
// • prints a visual representation
//    of the current board for reference (UI)
//
// Params: none
// I/O: outputs a basic 2D board with associated markings
// Return: void (nothing)
//-------------------------------------------------------
void printBoard()
{
    cout << endl;
    cout << setfill(' ') << setw(3);
    for(int c=0; c<dimensions; c++)
    { cout << c+1 << " ";}
    cout << endl;
    
    for (int x=0; x<dimensions; x++)
    {
        cout << x+1 << " ";
        for (int y=0; y<dimensions; y++)
        {
            switch (board[x][y])
            {
                case X:        cout << "X"; break;
                case O:        cout << "O"; break;
                case EMPTY:    cout << " "; break;
            }
            if ( y<(dimensions-1) )                          // column boundaries
            {cout << "|";}
        }
        if ( x<(dimensions-1) )                              // row boundaries
        {
            cout << "\n";
            cout << setfill(' ') << setw(4);
            for(int a=0; a<(dimensions-1); a++)
            {cout << "-+";}
            cout << "-\n";
        }
    }
    cout << endl;
}




//-------------------------------------------------
// Menu (function)
//
// • prints a menu for the user to select from (UI)
//
// Params: none
// I/O: outputs basic menu options
// Return: void (nothing)
//-------------------------------------------------
void Menu()
{
    cout << setw(29) << "Welcome to TIC TAC TOE!" << endl << endl;
        cout << "||--------------------------------||" << endl;
        cout << "||--------------------------------" << endl;
    cout << setw(15) << "Menu Options:" << setw(10) << "1. START" << endl;
    cout << setw(43) << "2. CHANGE BOARD (def. 2x2)" << endl;
        cout << "||________________________________" << endl;
        cout << "||________________________________||" << endl;
    cout << setw(12) << "select -> ";
}




//-----------------------------------------
// Divider (function)
//
// • prints a large divider section for UI
//
// Params: none
// I/O: outputs a decorative divider
// Return: void (nothing)
//-----------------------------------------
void Divider()
{
    cout << setfill('X') << setw(48) << 'X' << endl;
    cout << setfill('O') << setw(48) << 'O' << endl;
    cout << setfill('X') << setw(48) << 'X' << endl;
    cout << setfill('O') << setw(48) << 'O' << endl;
    cout << setfill('X') << setw(24) << "HELLO" << setw(24) << 'X' << endl;
    cout << setfill('O') << setw(48) << 'O' << endl;
    cout << setfill('X') << setw(48) << 'X' << endl;
    cout << setfill('O') << setw(48) << 'O' << endl;
    cout << setfill('X') << setw(48) << 'X' << endl;
    cout << endl;
}




//----------------------------------------------------
// BoardSettings (function)
//
// • prints a display allowing user to set board size
//
// Params: none
// I/O: outputs instructions for setting up the board
//      inputs board dimensions with limitation
//      outputs confirmation
// Return: void (nothing)
//----------------------------------------------------
void BoardSettings()
{
    cout << "BOARD SETTINGS" << endl;
    cout << "------------------------------------------------" << endl;
    cout << "(Directions)" << endl;
    cout << "choose a board with size 2 or greater" << endl;
    cout << "2 represents a 2x2 playing field" << endl << endl;
    cout << "Board Size: ";
    cin >> dimensions;
    
    while(dimensions < 2)
    {
        cout << endl;
        cout << "\"Your input was incorrect.\"\n";
        cout << "\"Please review the instructions carefully.\"\n";
        cout << endl;
        cout << "Board Size: ";
        cin >> dimensions;
    }
    cout << endl;
    cout << setfill('-') << setw(48) << '-' << endl;
    cout << dimensions << "x" << dimensions << " Tic Tac Toe" << endl;
    counter = dimensions*dimensions;
}

/**********************************************************************************************************/

// MAIN PROGRAM //

/*========================================================================================================*/

int main()
{
    bool start;
    int selection;
    char hold;
   
    Menu();
    cin >> selection;
    cout << endl;
    Divider();
    
    switch(selection)
    {
        case 1: start = true;
            break;
        case 2: start = false;
    }
    
    if(!start)
    {
        BoardSettings();
    }
    else
    {
        dimensions = 2;
        cout << setfill('-') << setw(48) << '-' << endl;
        cout << "2x2 Tic Tac Toe" << endl;
        counter = dimensions*dimensions;
    }
   
    // allocate board
    board = new int*[dimensions];          // allocating space for n rows
    for (int i = 0; i < dimensions; i++)
    {
        board[i] = new int[dimensions];    // allocating space for n cols per row
    }
    
    clearBoard();                          // clear the board and start with player X
    printBoard();                          // padded with new lines (currently empty)

    // putMarks and decrements counter each move.
    
    int row, col;
    
    do
    {
        // CURRENT PLAYER's TURN
        cout << endl;
        cout << "PLAYER ";
        switch(currentPlayer)
        {
            case 1: hold = 'X'; cout << hold;
                break;
            case -1: hold = 'O'; cout << hold;
        }
        cout << "'s TURN" << endl;
        cout << "\"remember to separate row and column\"" << endl;
        cout << "\"numbers by space\"" << endl;
        cout << endl;
    
        // CURRENT PLAYER's TURN
        cout << "Place " << hold << " at Position: ";
        cin >> row >> col;
    
        while(row > dimensions || col > dimensions || row < 1 || col < 1 || board[row-1][col-1] != EMPTY)
        {
            cout << "\"That position is out of bounds\"" << endl;
            cout << "\"Please refer to the numbers on the playing board\"" << endl;
            cout << endl;
            cout << "Place " << hold << " at Position: ";
            cin >> row >> col;
        }
        row--;
        col--;
        putMark(row,col);
        printBoard();
    }while(!isWin(X) && !isWin(O) && counter>0);
    
    int winner = getWinner();
    if (winner != EMPTY)
    {
        cout << endl;
        cout << (winner == X ? 'X' : 'O') << " wins" << endl;
    }
    else
        cout << endl << "Tie" << endl;

    // deallocating all allocated memory
    delete board;               // destroy board
    
    return 0;       // end program returning with exit code 0
}
