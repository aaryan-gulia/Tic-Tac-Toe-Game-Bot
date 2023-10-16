#include <iostream>
#include "Game.hpp"

using namespace std;
int main()
{
//  char play variable determines the progression into the game, re-start of the game, and exit from the game
    char play;
    cout<<"Do you want to play(y/n)? ";
    cin>>play;
    
//  This isn't the active game loop, but keeps the program running in between game instances
    while(play == 'y'){
//      I new instance of class Game is created eveytime a user wants to re-start a game and the board is reset
        Game game;
        cout<<"Do you want to play again(y/n)? ";
        cin>>play;
    }
    return 0;
}
