#ifndef BOARD_H
#define BOARD_H
#include<iostream>
#include<string>
#include<random>
#include"windows.h"
#include<time.h>
#include<stdlib.h>
using namespace std;
class Board{
public:
    int size;
    int direction[3]={-1,0,1};
    int keyboard[10][10];               //keyboard用来表示棋盘
    int mask[10][10];                   //mask用来表示是否插旗图
    
    /*Function:initialization
    Usage: initialization();
    ------------------------
    To set all the number in keyboard to -1(represent "Have not open")
    */
    void initialization();
    
    /*Function:mineCreate
    Usage:mineCreate()
    --------------------
    Randomly set 9 of the 81 places to be 9(represent Mine)*/
    void mineCreate();
    
    /*Function:printTrueNumber
    Usage:printTrueNumber()
    --------------------
    Print the current statue of the keyboard*/
    void printTrueNumber();
    
    /*Function:calculateMine
    Usage: int count=calculateMine(x,y)
    --------------------
    Calculate how much mines in the adjacent places of place (x,y)*/
    int calculateMine(int x,int y);
    
    /*Function:game
    Usage:int count=game(x,y)
    --------------------
    Playing the game, it will return -1 if game is over(both win and lose)
    If game is continue, it will judge what should do according to different situation
    1. Open a non-zero-mine place---> Show the number of it
    2. Open a zero-mine place---> It will call the expansion function*/
    int game(int x,int y);

    /*Function:expansion
    Usage:expansion(x,y)
    --------------------
    Calculate all the adjacent places of this zero place(x,y)
    If one of the adjacent place is still zero place, call expansion again in that place*/
    void expansion(int x,int y);
    
    /*Function:printMineforFinal
    Usage:printMineforFinal()
    -------------------------
    Print the output for the game-over situation:
    Show all places for Mines*/
    void printMineforFinal();
    
    /*Function:win()
    Usage:if (win())
    --------------------
    Check whether the user have won this game*/
    bool win();

};
#endif // BOARD_H
