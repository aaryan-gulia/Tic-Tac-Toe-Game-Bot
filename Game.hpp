#include <string.h>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <iostream>

using namespace std;
#include <stdio.h>

#ifndef Game_H
#define Game_H
class Game{
//This is the primary Game class, and sets attributes and functions for every game instance; the primary game loop is accessed through objects of the class
    public:
//  These variables are important definers of any state, including the board state, the token of the player and computer, and whose turn it is to play
    vector<vector<string>> board = {{" "," "," "},{" "," "," "},{" "," "," "}};
    string player, me;
    int turn;
    

    void drawBoard();
    
    void playerTurn();
    int myTurn();
    int checkState(vector<vector<string>> board);
    
    void startGame();
    void runGame();
    
    Game(){
        turn = 0;
        srand((unsigned) time(NULL));
        player = "ox"[rand() % 2];
        if (player == "x") me = "o";
        else me = "x";
        
        cout<<"You will play as "<<player<<endl;
        if(player == "x")turn = 1;
        runGame();
    }
};

#endif
//Impliment minimax algorithm with alpha-beta pruning.
