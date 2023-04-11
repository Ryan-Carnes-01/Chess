#include "chessfunctions.h"

enum Team {Black, White};

struct Conversion_Table{
    int numtable[9] = {8,7,6,5,4,3,2,1,0};
    int chartable[256];
    Conversion_Table(){
        int j = 0;
        for(int i = 65; i < 73; i++){
            chartable[i] = j;
            chartable[i+32] = j;
            j++;
        }
    }
};
struct Piece{
    vector<pair<int,int>> valid_moves;
    pair<int,int> location;
    Team color;
    int value;
    char symbol;
    bool firstmove;
};
struct Pawn: public Piece{
    Pawn(){
        value = 1;
        symbol = 'p';
        firstmove = true;
    }
};
struct Bishop: public Piece{
    Bishop(){
        value = 3;
        symbol = 'B';
    }
};
struct Knight: public Piece{
    Knight(){
        value = 3;
        symbol = 'N';
    }
};
struct Castle: public Piece{
    Castle(){
        value = 5;
        symbol = 'C';
    }
};
struct Queen: public Piece{
    Queen(){
        value = 8;
        symbol = 'Q'; 
    }
};
struct King: public Piece{
    King(){
        value = 10;
        symbol = 'K';
    }
};
struct Board{
    Piece ***board = new Piece**[8];
    Board(){
        for(int i = 0; i < 8; i++){board[i] = new Piece*[8];}
        board[0][0] = new Castle; board[0][1] = new Knight; board[0][2] = new Bishop; board[0][3] = new Queen; board[0][4] = new King; board[0][5] = new Bishop; board[0][6] = new Knight; board[0][7] = new Castle;
        board[7][0] = new Castle; board[7][1] = new Knight; board[7][2] = new Bishop; board[7][3] = new Queen; board[7][4] = new King; board[7][5] = new Bishop; board[7][6] = new Knight; board[7][7] = new Castle;
        for(int i = 0; i < 8; i++){
            board[1][i] = new Pawn; board[6][i] = new Pawn; 
            board[0][i]->location.first = 1; board[0][i]->location.second = i;
            board[1][i]->location.first = 1; board[1][i]->location.second = i;
            board[6][i]->location.first = 1; board[6][i]->location.second = i;
            board[7][i]->location.first = 1; board[7][i]->location.second = i;
            board[2][i] = NULL; board[3][i] = NULL; board[4][i] = NULL; board[5][i] = NULL; 
            board[0][i]->color = Black; board[1][i]->color = Black; board[6][i]->color = White; board[7][i]->color = White;
        }
    }
    void printboard(){
        cout << "  a   b   c   d   e   f   g   h";
        cout << "\n|-------------------------------|\n";
        for(int i = 0; i < 8; i++){
        cout << "| ";
        for(int j = 0; j < 8; j++){
            if(board[i][j] != NULL){
                cout << board[i][j]->symbol << " | ";
            }else{
                cout << " " << " | ";
            }
        }
        cout << 9 - (i + 1);
        cout << "\n|-------------------------------|\n";
        }
    }
    bool piececheck(pair<pair<int,int>,pair<int,int>> input){
        int piece_i,piece_j;
        piece_i = input.first.first;
        piece_j = input.first.second;
        if(board[piece_i][piece_j] == NULL){
            return false;
        }
        else return true;
    }
    bool movecheck(pair<pair<int,int>,pair<int,int>> input){
        vector<pair<int,int>>::iterator ptr;
        for(ptr = board[input.first.first][input.first.second]->valid_moves.begin(); ptr < board[input.first.first][input.first.second]->valid_moves.end(); ptr++){
            if(*ptr == input.second){return true;}
        }
        return false;
    }
    void update_moves(){
    /*
        pair<int,int>temp;
        cout << "beginning of update move\n";
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                cout << "for loop iteration: [" << i << "] [" << j << "]\n";
                if(board[i][j] != NULL){
                    if(board[i][j]->symbol == 'p'){
                        if(board[i][j]->color == White){
                            if(board[i-1][j] == NULL){ //move1
                                temp.first = i-1; temp.second = j;
                                board[i][j]->valid_moves.push_back(temp);
                            }
                            if(board[i-1][j+1] != NULL && board[i-1][j+1]->color != White){ //attack
                                temp.first = i-1; temp.second = j+1;
                                board[i][j]->valid_moves.push_back(temp);
                            }
                            if(board[i-1][j-1] != NULL && board[i-1][j-1]->color != White){ //attack
                                temp.first = i-1; temp.second = j-1;
                                board[i][j]->valid_moves.push_back(temp);
                            }
                            if(board[i-1][j] == NULL && board[i-2][j] == NULL && board[i][j]->firstmove == true){ //move2
                                temp.first = i-2; temp.second = j;
                                board[i][j]->valid_moves.push_back(temp);
                            }
                        }else{
                            if(board[i+1][j] == NULL){ //move1
                                temp.first = i+1; temp.second = j;
                                board[i][j]->valid_moves.push_back(temp);
                            }
                            if(board[i+1][j+1] != NULL && board[i+1][j+1]->color != White){ //attack
                                temp.first = i+1; temp.second = j+1;
                                board[i][j]->valid_moves.push_back(temp);
                            }
                            if(board[i+1][j-1] != NULL && board[i+1][j-1]->color != White){ //attack
                                temp.first = i+1; temp.second = j-1;
                                board[i][j]->valid_moves.push_back(temp);
                            }
                            if(board[i+1][j] == NULL && board[i+2][j] == NULL && board[i][j]->firstmove == true){ //move2
                                temp.first = i+2; temp.second = j;
                                board[i][j]->valid_moves.push_back(temp);
                            }
                        }
                    }
                    else if(board[i][j]->symbol == 'B'){}                    
                    else if(board[i][j]->symbol == 'N'){}                    
                    else if(board[i][j]->symbol == 'C'){}
                    else if(board[i][j]->symbol == 'Q'){}
                    else if(board[i][j]->symbol == 'K'){}
                    else{
                        //cerr << "Error with piece symbol in update_moves"; exit(1);
                    }
                }
            }
        }*/
    }
};
struct Chess{
    void printgreeting(){
        cout << " _   _   _  \n";
        cout << "| \\ / \\ / | \n";
        cout << "\\_________/ \n";
        cout << " |       |  \n";
        cout << " |       |  \n";
        cout << " |       |  \n";
        cout << " /_______\\  \n";
        cout << "|_________| \n";
        cout << "Welcome to Chess++, a console-based chess program made in C++\n";
        system("pause");
        system("cls");
    }
    bool run(){
        bool checkmate = false;
        Board gameboard;
        Conversion_Table ctable;
        pair<pair<int,int>,pair<int,int>>input;
        gameboard.printboard();
        cout << "before  update move\n";
        gameboard.update_moves();
        cout << "afetr update move\n";
        //vLOOPv
        //while(checkmate == false)
        //playerinput
        input = convertcoords(ctable.numtable, ctable.chartable, playerinput());
        //piececheck
        if(gameboard.piececheck(input) == false){
            cout << "not a valid piece\n";
        };
        if(gameboard.movecheck(input) == false){
            cout << "not a valid move\n";
        }
        //movecheck
        //checkcheck
        //playermove
        //printboard
        gameboard.printboard();
        return false;
    }
    void printvictory(){
        cout << "You win\n";
    }
    void printdefeat(){
        cout << "You lose\n";
    }
};