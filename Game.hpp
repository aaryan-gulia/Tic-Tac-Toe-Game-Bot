#include <string.h>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <iostream>

#include <stdio.h>

#ifndef Game_H
#define Game_H

class Game{
    //This is the primary Game class, and sets attributes and functions for every game instance; the primary game loop is accessed through objects of the class
private:
    std::vector<std::vector<std::string>> board;
    enum turn{
        player_turn = 0,
        my_turn = 1
    }current_turn;
    enum game_state{
        player_lost = -1,
        game_on = 0,
        player_won = 1,
        game_tied = 2
    }current_game_state;
    
    void drawBoard();
    void playerTurn();
    int myTurn();
    
    int checkState(std::vector<std::vector<std::string>> board);
    void runGame();
    void endGame();
public:
    //  These variables are important definers of any state, including the board state, the token of the player and computer, and whose turn it is to play
    std::string player, me;
    
    Game();
};

#endif
//Impliment minimax algorithm with alpha-beta pruning.
