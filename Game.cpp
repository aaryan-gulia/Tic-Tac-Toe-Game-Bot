
#include "Game.hpp"
using namespace std;

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
                if(checkState(boardTemp) == 1){
                    board[i][j] = me;
                    turn = 1;return 0;
                }
                boardTemp[i][j] = player;
                if(checkState(boardTemp) == -1){
                    board[i][j] = me;
                    turn = 1;return 0;
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
                turn = 1;return 0;
            }
        }
    }
    for(int i = 0;i < 3;i++){
        for(int j = 0;j<3;j++){
            if(board[i][j] == " " && i%2 == 0 && j%2 == 0){
                board[i][j] = me;
                turn = 1;return 0;
            }
        }
    }
    for(int i = 0;i < 3;i++){
        for(int j = 0;j<3;j++){
            if(board[i][j] == " "){
                board[i][j] = me;
                turn = 1;return 0;
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
            cout<<"enter a valid move "<<endl;
            cin>>row>>col;
        }
    } while (true);
    
    turn = 0;
    runGame();
}

void Game::runGame(){
    drawBoard();
    switch (checkState(board)) {
        case 0:
            if(turn == 1){
                playerTurn();
                break;
            }
            else if(turn == 0){
                myTurn();
                runGame();
                break;
            }
        case -1:
            drawBoard();
            cout<<"Nicely done, YOU WON!"<<endl;
            break;
        case 1:
            drawBoard();
            cout<<"Better luck next time, I WON!"<<endl;
            break;
        case 2:
            drawBoard();
            cout<<"That was close, ITS A TIE!"<<endl;
            break;
        default:
            drawBoard();
            cout<<"Something went wrong"<<endl;
            break;
    }
}



int Game::checkState(vector<vector<string>> board){
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
        if ((boardInt[j] + boardInt[j + 3] + boardInt[j + 6]) == 3) return 1;
        else if ((boardInt[j] + boardInt[j + 3] + boardInt[j + 6]) == -3) return -1;
    }
    
    if ((boardInt[i] + boardInt[i + 1] + boardInt[i + 2]) == 3) return 1;
    else if ((boardInt[i+3] + boardInt[i + 4] + boardInt[i + 5]) == 3) return 1;
    else if ((boardInt[i+6] + boardInt[i + 7] + boardInt[i + 8]) == 3) return 1;
    else if ((i == 2) && (boardInt[i] + boardInt[i + 2] + boardInt[i + 4]) == 3) return 1;
    else if ((i == 0) && (boardInt[i] + boardInt[i + 4] + boardInt[i + 8]) == 3) return 1;
    
    else if ((boardInt[i] + boardInt[i + 1] + boardInt[i + 2]) == -3) return -1;
    else if ((boardInt[i] + boardInt[i + 3] + boardInt[i + 6]) == -3) return -1;
    else if ((boardInt[i+3] + boardInt[i + 4] + boardInt[i + 5]) == -3) return -1;
    else if ((boardInt[i+6] + boardInt[i + 7] + boardInt[i + 8]) == -3) return -1;
    else if ((i == 2) && (boardInt[i] + boardInt[i + 2] + boardInt[i + 4]) == -3) return -1;
    else if ((i == 0) && (boardInt[i] + boardInt[i + 4] + boardInt[i + 8]) == -3) return -1;

    if (blank == 0) return 2;

    return 0;
}

