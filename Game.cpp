
#include "Game.hpp"
using namespace std;

Game::Game(){
    board = {{" "," "," "},{" "," "," "},{" "," "," "}};
    current_turn = my_turn;
    srand((unsigned) time(NULL));
    player = "ox"[rand() % 2];
    if (player == "x") me = "o";
    else me = "x";
    
    cout<<"You will play as "<<player<<endl;
    if(player == "x")current_turn = player_turn;
    runGame();
}

void Game::drawBoard(){
    /*The drawBoard method of the Game class can be called upon to draw the current board state
     at any point in the game to the ostream; it uses the public variable called board to do so*/
    for(auto c = board.begin();c != board.end();c++) {
        cout<<"|"<<setw(2)<<(*c)[0]<<setw(2)<<"|"<<setw(2)<<(*c)[1]<<setw(2)<<"|"<<setw(2)<<(*c)[2]<<setw(2)<<"|"<<endl;
        if (c != board.end()-1)
        cout<<"-------------"<<endl;
        else cout<<"\n";
    }
}

int Game::myTurn(){
    /*The myTurn method implements a basic algorithm that ensure it acts on the possibility of victory
     or defeat in the next turn; if no such possibility is identified, the method still takes an intelligent approch by prioratising free spaces on the corners, then looking at the free space at the center, and only then settling for the edges*/
    
//    temperory copy of the board on which future predictions can be made
    vector<vector<string>> boardTemp = board;
  
//    Loop to check how a move on any given position would affect the next steps in the game
    for(int i = 0;i < 3;i++){
        for(int j = 0; j<3;j++){
            if(board[i][j] == " "){
                boardTemp[i][j] = me;
                if(checkState(boardTemp) == player_lost){
                    board[i][j] = me;
                    return 0;
                }
                boardTemp[i][j] = player;
                if(checkState(boardTemp) == player_won){
                    board[i][j] = me;
                    return 0;
                }
                boardTemp[i][j] = " ";
            }
        }

//  psuedo-random intelligent approach to move selection if no immediate objective is found
    }
    for(int i = 0;i < 3;i++){
        for(int j = 0;j<3;j++){
            if(board[i][j] == " " && i%2 == 0 && j%2 == 0 && ((i + j) != 2 || i == 0 || j == 0)){
                board[i][j] = me;
                return 0;
            }
        }
    }
    for(int i = 0;i < 3;i++){
        for(int j = 0;j<3;j++){
            if(board[i][j] == " " && i%2 == 0 && j%2 == 0){
                board[i][j] = me;
                return 0;
            }
        }
    }
    for(int i = 0;i < 3;i++){
        for(int j = 0;j<3;j++){
            if(board[i][j] == " "){
                board[i][j] = me;
                return 0;
            }
        }
    }

    cout<<"Something went wrong";
    return 0;
}



void Game::playerTurn(){
    /*This method is called to let the player enter their move. This will set some rules they need to follow*/
    int row,col;
    cout<<"What's your move? \n";
    cin>>row>>col;
    
//    control loop ensures user entered values are in range and faulty values don't create undefined errors
    do {
        if(row > 0 && row <= 3 && col > 0 && col <= 3 && board[row-1][col-1]==" "){
            board[row-1][col-1] = player;
            break;
        }
        else{
            cout<<"Play a valid move \nEnter two integers (row col): "<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin>>row>>col;
        }
    } while (true);
}

void Game::runGame(){
//    this is the main game loop; I use a do-while statement to efficiently handle the game instances' lifesycle
    do {
        if(current_turn == player_turn){
            playerTurn();
            current_turn = my_turn;
        }
        else if(current_turn == my_turn){
            myTurn();
            current_turn = player_turn;
        }
        drawBoard();
        current_game_state = (game_state)checkState(board);
    } while (current_game_state == game_on);
    endGame();
}

int Game::checkState(vector<vector<string>> board){
    /*This function checks the state of the game when necessary. It is used at two times - by the runGame
     method to check what should be displayed or which process should be initiated, and by the myTurn
     method to predict future game states.*/
    std::unordered_map<std::string, int> stringToInteger = {{" ", 0},{me, 1},{player, -1}};
    int boardInt[9];
    int blank = 0,k=0,i=0;
    for(int i = 0;i < 3;i++){
        for(int j = 0;j<3;j++){
            if(board[i][j] == " ")blank++;
            boardInt[k] = stringToInteger[board[i][j]];
            k++;
        }
    }
    for(int j = 0; j<3;j++){
        if ((boardInt[j] + boardInt[j + 3] + boardInt[j + 6]) == 3) return player_lost;
        else if ((boardInt[j] + boardInt[j + 3] + boardInt[j + 6]) == -3) return player_won;
    }
    
    if ((boardInt[i] + boardInt[i + 1] + boardInt[i + 2]) == 3) return player_lost;
    else if ((boardInt[i+3] + boardInt[i + 4] + boardInt[i + 5]) == 3) return player_lost;
    else if ((boardInt[i+6] + boardInt[i + 7] + boardInt[i + 8]) == 3) return player_lost;
    else if ((i == 2) && (boardInt[i] + boardInt[i + 2] + boardInt[i + 4]) == 3) return player_lost;
    else if ((i == 0) && (boardInt[i] + boardInt[i + 4] + boardInt[i + 8]) == 3) return player_lost;
    
    else if ((boardInt[i] + boardInt[i + 1] + boardInt[i + 2]) == -3) return player_won;
    else if ((boardInt[i+3] + boardInt[i + 4] + boardInt[i + 5]) == -3) return player_won;
    else if ((boardInt[i+6] + boardInt[i + 7] + boardInt[i + 8]) == -3) return player_won;
    else if ((i == 2) && (boardInt[i] + boardInt[i + 2] + boardInt[i + 4]) == -3) return player_won;
    else if ((i == 0) && (boardInt[i] + boardInt[i + 4] + boardInt[i + 8]) == -3) return player_won;

    if (blank == 0) return game_tied;

    return game_on;
}


void Game::endGame(){
    switch(current_game_state){
        case player_lost: {
            cout<< "Better luck next time, YOU LOST.\n";
            break;
        }
        case player_won: {
            cout<< "You got me there, YOU WON!\n";
            break;
        }
        case game_tied: {
            cout<< "That was a close one, THE GAME TIED!\n";
            break;
        }
    }
}
