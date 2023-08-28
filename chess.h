//maybe I should generate every piece's valid moves each turn in order to track check/checkmates, instead of generating
//a piece's move when selected.
//then I can just check this list for whatever piece i choose instead of generating on the spot
//Need to figure out how to detect a check/checkmate, and when a piece moving will result in check (making that move invalid)

//Castling L and R
//En Passant
//Pawn Promotion

#include "chessfunctions.h"
#define RED "\033[31m" //(white)
#define BLUE "\033[34m" //(black)
#define RESET "\033[0m"
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
    pair<int,int> location;
    Team color;
    int value;
    char symbol;
    bool firstmove;

    virtual vector<pair<int,int>> generate_valid_moves (Piece***){
        return vector<pair<int,int>>();
    };
};
struct Pawn: public Piece{
    Pawn(){
        value = 1;
        symbol = 'p';
        firstmove = true;
    }
    vector<pair<int,int>> generate_valid_moves(Piece*** board) override {
        vector<pair<int,int>> valid_moves;
        pair<int,int> move;
        if(color == White){//IF WHITE
            if(location.first-1 < 0){return valid_moves;} //at edge of board, no moves
            if(board[location.first-1][location.second] == NULL){
                //valid move - 1 square
                move.first = location.first-1; move.second = location.second;
                valid_moves.push_back(move);
                if(location.first-2 >= 0){
                    if(board[location.first-2][location.second] == NULL && firstmove){
                        //valid move - 2 square
                        move.first = location.first-2; move.second = location.second;
                        valid_moves.push_back(move);
                    }
                }
            }
            //check if y+1 out of bounds
            if(location.second + 1 <= 7){
                if(board[location.first-1][location.second+1] != NULL){
                    if(board[location.first-1][location.second+1]->color == Black){
                        //valid move - capture right black
                        move.first = location.first-1; move.second = location.second+1;
                        valid_moves.push_back(move);
                    }
                }
            }
            //check if y-1 out of bounds
            if(location.second - 1 >= 0){
                if(board[location.first-1][location.second-1] != NULL){
                    if(board[location.first-1][location.second-1]->color == Black){
                     //valid move - capture left black
                        move.first = location.first-1; move.second = location.second-1;
                        valid_moves.push_back(move);
                    }
                }
            }
        }else{ //IF BLACK
            if(location.first+1 > 7){return valid_moves;} //at edge of board, no moves
            if(board[location.first+1][location.second] == NULL){
                //valid move - 1 square
                move.first = location.first+1; move.second = location.second;
                valid_moves.push_back(move);
                if(location.first+2 <= 7){
                    if(board[location.first+2][location.second] == NULL && firstmove){
                        //valid move - 2 square
                        move.first = location.first+2; move.second = location.second;
                        valid_moves.push_back(move);
                    }
                }
            }
            //check if y+1 out of bounds
            if(location.second + 1 <= 7){
                if(board[location.first+1][location.second+1] != NULL){
                    if(board[location.first+1][location.second+1]->color == White){
                        //valid move - capture right white
                        move.first = location.first+1; move.second = location.second+1;
                        valid_moves.push_back(move);
                    }
                }
            }
            if(location.second - 1 >= 0){
                if(board[location.first+1][location.second-1] != NULL){
                    if(board[location.first+1][location.second-1]->color == White){
                        //valid move - capture left white
                        move.first = location.first+1; move.second = location.second-1;
                        valid_moves.push_back(move);
                    }
                }
            }
        }
        return valid_moves;
    }
};
struct Bishop: public Piece{
    Bishop(){
        value = 3;
        symbol = 'B';
    }
    vector<pair<int,int>> generate_valid_moves(Piece*** board) override {
        vector<pair<int,int>> valid_moves;
        pair<int,int> move;
        int row = this->location.first;
        int col = this->location.second;
        int i = 1;
        //row+1 col+1
        while(row+i <= 7 && col+i <= 7){
            if(board[row+i][col+i] == NULL){ //valid move - empty square
                move.first = row+i;
                move.second = col+i;
                valid_moves.push_back(move);
            }else if(board[row+i][col+i]->color != this->color){ //valid move - capture
                move.first = row+i;
                move.second = col+i;
                valid_moves.push_back(move);
                break;
            }else{
                break;
            }
            i++;
        }i = 1;
        //row+1 col-1
        while(row+i <= 7 && col-i >= 0){
            if(board[row+i][col-i] == NULL){
                move.first = row+i;
                move.second = col-i;
                valid_moves.push_back(move);
            }else if(board[row+i][col-i]->color != this->color){
                move.first = row+i;
                move.second = col-i;
                valid_moves.push_back(move);
                break;
            }else{
                break;
            }
            i++;
        }i = 1;
        //row-1 col+1
        while(row-i >= 0 && col+i <= 7){
            if(board[row-i][col+i] == NULL){
                move.first = row-i;
                move.second = col+i;
                valid_moves.push_back(move);
            }else if(board[row-i][col+i]->color != this->color){
                move.first = row-i;
                move.second = col+i;
                valid_moves.push_back(move);
                break;
            }else{
                break;
            }
            i++;
        }i = 1;
        //row-1 col-1
        while(row-i >= 0 && col-i >= 0){
            if(board[row-i][col-i] == NULL){
                move.first = row-i;
                move.second = col-i;
                valid_moves.push_back(move);
            }else if(board[row-i][col-i]->color != this->color){
                move.first = row-i;
                move.second = col-i;
                valid_moves.push_back(move);
                break;
            }else{
                break;
            }
            i++;
        }
        return valid_moves;
    }
};
struct Knight: public Piece{
    Knight(){
        value = 3;
        symbol = 'N';
    }
    vector<pair<int,int>> generate_valid_moves(Piece*** board) override {
        vector<pair<int,int>> valid_moves;
        pair<int,int> move;
        int row = this->location.first;
        int col = this->location.second;
        //8 possible locations
        //row+1 col+2
        if(row+1 <= 7 && col+2 <= 7){
            if(board[row+1][col+2] == NULL){
                //valid move - open square
                move.first = row+1; move.second = col+2;
                valid_moves.push_back(move);
            }else if(board[row+1][col+2]->color != this->color){
                //valid move - capture
                move.first = row+1; move.second = col+2;
                valid_moves.push_back(move);
            }
        }
        //row+2 col+1
        if(row+2 <= 7 && col+1 <= 7){
            if(board[row+2][col+1] == NULL){
                //valid move - open square
                move.first = row+2; move.second = col+1;
                valid_moves.push_back(move);
            }else if(board[row+2][col+1]->color != this->color){
                //valud move - capture
                move.first = row+2; move.second = col+1;
                valid_moves.push_back(move);
            }
        }

        //row-1 col+2 
        if(row-1 >= 0 && col+2 <= 7){
            if(board[row-1][col+2] == NULL){
                //valid move - open square
                move.first = row-1; move.second = col+2;
                valid_moves.push_back(move);
            }else if(board[row-1][col+2]->color != this->color){
                //valid move - capture
                move.first = row-1; move.second = col+2;
                valid_moves.push_back(move);
            }
        }
        //row+2 col-1 
        if(row+2 <= 7 && col-1 >= 0){
            if(board[row+2][col-1] == NULL){
                //valid move - open square
                move.first = row+2; move.second = col-1;
                valid_moves.push_back(move);
            }else if(board[row+2][col-1]->color != this->color){
                //valud move - capture
                move.first = row+2; move.second = col-1;
                valid_moves.push_back(move);
            }
        }

        //row+1 col-2 
        if(row+1 <= 7 && col-2 >= 0){
            if(board[row+1][col-2] == NULL){
                //valid move - open square
                move.first = row+1; move.second = col-2;
                valid_moves.push_back(move);
            }else if(board[row+1][col-2]->color != this->color){
                //valid move - capture
                move.first = row+1; move.second = col-2;
                valid_moves.push_back(move);
            }
        }
        //row-2 col+1 
        if(row-2 >= 0 && col+1 <= 7){
            if(board[row-2][col+1] == NULL){
                //valid move - open square
                move.first = row-2; move.second = col+1;
                valid_moves.push_back(move);
            }else if(board[row-2][col+1]->color != this->color){
                //valud move - capture
                move.first = row-2; move.second = col+1;
                valid_moves.push_back(move);
            }
        }

        //row-1 col-2 
        if(row-1 >= 0 && col-2 >= 0){
            if(board[row-1][col-2] == NULL){
                //valid move - open square
                move.first = row-1; move.second = col-2;
                valid_moves.push_back(move);
            }else if(board[row-1][col-2]->color != this->color){
                //valid move - capture
                move.first = row-1; move.second = col-2;
                valid_moves.push_back(move);
            }
        }
        //row-2 col-1 
        if(row-2 >= 0 && col-1 >= 0){
            if(board[row-2][col-1] == NULL){
                //valid move - open square
                move.first = row-2; move.second = col-1;
                valid_moves.push_back(move);
            }else if(board[row-2][col-1]->color != this->color){
                //valud move - capture
                move.first = row-2; move.second = col-1;
                valid_moves.push_back(move);
            }
        }

        return valid_moves;
    }
};
struct Castle: public Piece{
    Castle(){
        value = 5;
        symbol = 'C';
        firstmove = true;
    }
    vector<pair<int,int>> generate_valid_moves(Piece*** board) override {
        vector<pair<int,int>> valid_moves;
        pair<int,int> move;
        int row = this->location.first;
        int col = this->location.second;
        int i = 1;
        while(row+i <= 7){
            move.second = col;
            if(board[row+i][col] == NULL){
                //valid move - empty square
                move.first = row+i;
                valid_moves.push_back(move);
            }else if(board[row+i][col]->color != this->color){
                //valid move - capture
                move.first = row+i;
                valid_moves.push_back(move);
                break;
            }else{
                break;
            }
            i++;
        } i = 1;
        while(row-i >= 0){
            move.second = col;
            if(board[row-i][col] == NULL){
                //valid move - empty square
                move.first = row-i;
                valid_moves.push_back(move);
            }else if(board[row-i][col]->color != this->color){
                //valid move - capture
                move.first = row-i;
                valid_moves.push_back(move);
                break;
            }else{
                break;
            }
            i++;
        } i = 1;
        while(col+i <= 7){
            move.first = row;
            if(board[row][col+i] == NULL){
                //valid move - empty square
                move.second = col+i;
                valid_moves.push_back(move);
            }else if(board[row][col+i]->color != this->color){
                //valid move - capture
                move.second = col+i;
                valid_moves.push_back(move);
                break;
            }else{
                break;
            }
            i++;
        } i = 1;
        while(col-i >= 0){
            move.first = row;
            if(board[row][col-i] == NULL){
                //valid move - empty square
                move.second = col-i;
                valid_moves.push_back(move);
            }else if(board[row][col-i]->color != this->color){
                //valid move - capture
                move.second = col-i;
                valid_moves.push_back(move);
                break;
            }else{
                break;
            }
            i++;
        }
        return valid_moves;
    }
};
struct Queen: public Piece{
    Queen(){
        value = 8;
        symbol = 'Q'; 
    }
    vector<pair<int,int>> generate_valid_moves(Piece*** board) override {
        vector<pair<int,int>> valid_moves;
        //loop over all 8 diagonals/horizontals/verticals adding to valid moves until a piece is blocking the path
        //if piece is opposing color, add to valid moves
        pair<int,int> move;
        int row = this->location.first;
        int col = this->location.second;
        int i = 1;
        //horizontal/vertical checks
        while(row+i <= 7){
            move.second = col;
            if(board[row+i][col] == NULL){
                //valid move - empty square
                move.first = row+i;
                valid_moves.push_back(move);
            }else if(board[row+i][col]->color != this->color){
                //valid move - capture
                move.first = row+i;
                valid_moves.push_back(move);
                break;
            }else{
                break;
            }
            i++;
        } i = 1;
        while(row-i >= 0){
            move.second = col;
            if(board[row-i][col] == NULL){
                //valid move - empty square
                move.first = row-i;
                valid_moves.push_back(move);
            }else if(board[row-i][col]->color != this->color){
                //valid move - capture
                move.first = row-i;
                valid_moves.push_back(move);
                break;
            }else{
                break;
            }
            i++;
        } i = 1;
        while(col+i <= 7){
            move.first = row;
            if(board[row][col+i] == NULL){
                //valid move - empty square
                move.second = col+i;
                valid_moves.push_back(move);
            }else if(board[row][col+i]->color != this->color){
                //valid move - capture
                move.second = col+i;
                valid_moves.push_back(move);
                break;
            }else{
                break;
            }
            i++;
        } i = 1;
        while(col-i >= 0){
            move.first = row;
            if(board[row][col-i] == NULL){
                //valid move - empty square
                move.second = col-i;
                valid_moves.push_back(move);
            }else if(board[row][col-i]->color != this->color){
                //valid move - capture
                move.second = col-i;
                valid_moves.push_back(move);
                break;
            }else{
                break;
            }
            i++;
        } i = 1;
        //diagonal checks
        //row+1 col+1
        while(row+i <= 7 && col+i <= 7){
            if(board[row+i][col+i] == NULL){ //valid move - empty square
                move.first = row+i;
                move.second = col+i;
                valid_moves.push_back(move);
            }else if(board[row+i][col+i]->color != this->color){ //valid move - capture
                move.first = row+i;
                move.second = col+i;
                valid_moves.push_back(move);
                break;
            }else{
                break;
            }
            i++;
        }i = 1;
        //row+1 col-1
        while(row+i <= 7 && col-i >= 0){
            if(board[row+i][col-i] == NULL){
                move.first = row+i;
                move.second = col-i;
                valid_moves.push_back(move);
            }else if(board[row+i][col-i]->color != this->color){
                move.first = row+i;
                move.second = col-i;
                valid_moves.push_back(move);
                break;
            }else{
                break;
            }
            i++;
        }i = 1;
        //row-1 col+1
        while(row-i >= 0 && col+i <= 7){
            if(board[row-i][col+i] == NULL){
                move.first = row-i;
                move.second = col+i;
                valid_moves.push_back(move);
            }else if(board[row-i][col+i]->color != this->color){
                move.first = row-i;
                move.second = col+i;
                valid_moves.push_back(move);
                break;
            }else{
                break;
            }
            i++;
        }i = 1;
        //row-1 col-1
        while(row-i >= 0 && col-i >= 0){
            if(board[row-i][col-i] == NULL){
                move.first = row-i;
                move.second = col-i;
                valid_moves.push_back(move);
            }else if(board[row-i][col-i]->color != this->color){
                move.first = row-i;
                move.second = col-i;
                valid_moves.push_back(move);
                break;
            }else{
                break;
            }
            i++;
        }
        return valid_moves;
    }
};
struct King: public Piece{
    King(){
        value = 10;
        symbol = 'K';
        firstmove = true;
    }
    vector<pair<int,int>> generate_valid_moves(Piece*** board) override {
        //TODO make this also check and generate possible castling options as valid moves
        vector<pair<int,int>> valid_moves;
        pair<int,int> move;
        int row = this->location.first;
        int col = this->location.second;
        //check all 8 adjacent squares
        //row+1
        if(row+1 <= 7){
            if(board[row+1][col] == NULL){
                //valid move
                move.first = row+1; move.second = col;
                valid_moves.push_back(move);
            }else if(board[row+1][col]->color != this->color){
                //valid move
                move.first = row+1; move.second = col;
                valid_moves.push_back(move);
            }
        }
        //row-1
        if(row-1 >= 0){
            if(board[row-1][col] == NULL){
                //valid move
                move.first = row-1; move.second = col;
                valid_moves.push_back(move);
            }else if(board[row-1][col]->color != this->color){
                //valid move
                move.first = row-1; move.second = col;
                valid_moves.push_back(move);
            }    
        }
        //col+1
        if(col+1 <= 7){
            if(board[row][col+1] == NULL){
                //valid move
                move.first = row; move.second = col+1;
                valid_moves.push_back(move);
            }else if(board[row][col+1]->color != this->color){
                //valid move
                move.first = row; move.second = col+1;
                valid_moves.push_back(move);
            }
        }
        //col-1
        if(col-1 >= 0){
            if(board[row][col-1] == NULL){
                //valid move
                move.first = row; move.second = col-1;
                valid_moves.push_back(move);
            }else if(board[row][col-1]->color != this->color){
                //valid move
                move.first = row; move.second = col-1;
                valid_moves.push_back(move);
            }            
        }
        //row+1 col+1
        if(row+1 <= 7 && col+1 <= 7){
            if(board[row+1][col+1] == NULL){
                //valid move
                move.first = row+1; move.second = col+1;
                valid_moves.push_back(move);
            }else if(board[row+1][col+1]->color != this->color){
                //valid move
                move.first = row+1; move.second = col+1;
                valid_moves.push_back(move);
            }            
        }
        //row+1 col-1
        if(row+1 <= 7 && col-1 >= 0){
            if(board[row+1][col-1] == NULL){
                //valid move
                move.first = row+1; move.second = col-1;
                valid_moves.push_back(move);
            }else if(board[row+1][col-1]->color != this->color){
                //valid move
                move.first = row+1; move.second = col-1;
                valid_moves.push_back(move);
            }            
        }
        //row-1 col+1
        if(row-1 >= 0 && col+1 <= 7){
            if(board[row-1][col+1] == NULL){
                //valid move
                move.first = row-1; move.second = col+1;
                valid_moves.push_back(move);
            }else if(board[row-1][col+1]->color != this->color){
                //valid move
                move.first = row-1; move.second = col+1;
                valid_moves.push_back(move);
            }            
        }
        //row-1 col-1
        if(row-1 >= 0 && col-1 >= 0){
            if(board[row-1][col-1] == NULL){
                //valid move
                move.first = row-1; move.second = col-1;
                valid_moves.push_back(move);
            }else if(board[row-1][col-1]->color != this->color){
                //valid move
                move.first = row-1; move.second = col-1;
                valid_moves.push_back(move);
            }            
        }

        return valid_moves;
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
            board[0][i]->location.first = 0; board[0][i]->location.second = i;
            board[1][i]->location.first = 1; board[1][i]->location.second = i;
            board[6][i]->location.first = 6; board[6][i]->location.second = i;
            board[7][i]->location.first = 7; board[7][i]->location.second = i;
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
                if(board[i][j]->color == Black){
                    cout << BLUE << board[i][j]->symbol << RESET << " | ";
                }else{
                    cout << RED << board[i][j]->symbol << RESET << " | ";
                }
            }else{
                cout << " " << " | ";
            }
        }
        cout << 9 - (i + 1);
        cout << "\n|-------------------------------|\n";
        }
    }
    bool checkcheck(Team turn){
        pair<int,int> kingcoords;
        vector<vector<pair<int,int>>> valid_moves;
        //get coords of turn-colored king & generate all possible moves for non turn-colored pieces
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                if(board[i][j] != NULL){
                    if(board[i][j]->color == turn && board[i][j]->value == 10){
                        kingcoords.first = i;
                        kingcoords.second = j;
                    }
                    if(board[i][j]->color != turn){valid_moves.push_back(board[i][j]->generate_valid_moves(board));}
                }
            }
        }
        //if king coords match any of these moves return true
        for(auto it1 = valid_moves.begin(); it1 != valid_moves.end(); it1++){
            vector<pair<int,int>>& piece_moves = *it1;
            for(auto it2 = piece_moves.begin(); it2 != piece_moves.end(); it2++){
                pair<int,int> move = *it2;
                if(move.first == kingcoords.first && move.second == kingcoords.second){
                    return true;
                }
            }
        }
        return false;
    }
    bool matecheck(Team turn){
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Piece* piece = board[i][j];
                if (piece != NULL && piece->color == turn) {
                    // Check if the piece has any legal moves to get the king out of check
                    vector<pair<int, int>> legalMoves = piece->generate_valid_moves(board);
                    for (const auto& move : legalMoves) {
                        pair<pair<int, int>, pair<int, int>> input = make_pair(make_pair(i, j), move);
                        if (!pincheck(input, turn)) {
                            // At least one legal move found, not checkmate
                           return false;
                       }
                    }
                }
            }
        }
        return true;
    }
    bool piececheck(pair<pair<int,int>,pair<int,int>> input, Team turn){
        int piece_i,piece_j;
        piece_i = input.first.first;
        piece_j = input.first.second;
        if(board[piece_i][piece_j] == NULL){
            return false;
        }
        if(board[piece_i][piece_j]->color != turn){
            return false;
        }
        return true;
    }
    bool movecheck(pair<pair<int,int>,pair<int,int>> input){ //generate and check valid moves against input
        vector<pair<int,int>> valid_moves;
        Piece* curPiece = board[input.first.first][input.first.second];
        valid_moves = curPiece->generate_valid_moves(board);
        for(auto it = valid_moves.begin(); it != valid_moves.end(); it++){
            if(it->first == input.second.first && it->second == input.second.second){return true;}
        }
        return false;
    }
    bool pincheck(pair<pair<int,int>,pair<int,int>> input, Team turn){ 
        int selectedrow = input.first.first;
        int selectedcol = input.first.second;
        int targetrow = input.second.first;
        int targetcol = input.second.second;
        //set pointer to target location/copy it's data
        Piece* temp = board[targetrow][targetcol];
        //make move temporarily
        board[targetrow][targetcol] = board[selectedrow][selectedcol];
        board[selectedrow][selectedcol] = NULL;
        board[targetrow][targetcol]->location.first = targetrow;
        board[targetrow][targetcol]->location.second = targetcol;
        //call checkcheck
        bool kingincheck = checkcheck(turn);
        //undo move
        board[selectedrow][selectedcol] = board[targetrow][targetcol];
        board[targetrow][targetcol] = temp;
        board[selectedrow][selectedcol]->location.first = selectedrow;
        board[selectedrow][selectedcol]->location.second = selectedcol;

        return kingincheck;
    }
    void move(pair<pair<int,int>,pair<int,int>> input, char promotedPiece){
        //move piece
    board[input.second.first][input.second.second] = board[input.first.first][input.first.second];
    if(board[input.second.first][input.second.second]->symbol == 'p' && (input.second.first == 0 || input.second.first == 7)){
        switch (promotedPiece) {
            case 'Q':  // Queen
                board[input.second.first][input.second.second] = new Queen;
                break;
            case 'B':  // Bishop
                board[input.second.first][input.second.second] = new Bishop;
                break;
            case 'N':  // Knight
                board[input.second.first][input.second.second] = new Knight;
                break;
            case 'R':  // Rook
                board[input.second.first][input.second.second] = new Castle;
                break;
            default:
                break;
        }
        // Set the color and location of the promoted piece
        board[input.second.first][input.second.second]->color = board[input.first.first][input.first.second]->color;
        board[input.second.first][input.second.second]->location = input.second;
    }
        board[input.first.first][input.first.second] = NULL;
        //update piece with new coords
        board[input.second.first][input.second.second]->location.first = input.second.first;
        board[input.second.first][input.second.second]->location.second = input.second.second;
        if(board[input.second.first][input.second.second]->firstmove){board[input.second.first][input.second.second]->firstmove = false;}
        return;
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
        cout << "| Red = White | Blue = Black |\n";
        cout << "Type 'help' to learn how to input moves" << endl;
        system("pause");
        system("cls");
    }
    Team run(){
        Team winner;
        Team turn = White;
        Board gameboard;
        Conversion_Table ctable;
        pair<pair<int,int>,pair<int,int>>input,rawinput;
        gameboard.printboard();
        cout << "White's turn" << endl;
        //vLOOPv-----------------
        while(1){
            //detect check/mate
            if(gameboard.checkcheck(turn)){
                if(gameboard.matecheck(turn)){
                    if(turn == White){winner = Black;}
                    else{winner = White;}
                    return winner;
                    break;
                }
                if(turn == White){cout << "White is in check" << endl;}
                else{cout << "Black is in check" << endl;}
            }
            //input
            rawinput = playerinput();
            if(rawinput.first.second == -1 && rawinput.second.second == -1){ //input is not a move
                char option = rawinput.first.first;
                if(option == 'z'){ //help message/invalid input/not a move
                    continue;
                }
                else if(option == 'k'){//castle kingside
                    if(turn == White){
                        //check that white king position has white king && firstmove
                        //check that white Krook position has white Krook && firstmove
                    }else{
                        //check that black king position has black king && firstmove
                        //check that white Krook position has white Krook && firstmove
                    }
                    continue;
                }
                else if(option == 'q'){
                    if(turn == White){
                        //check that white king position has white king && firstmove
                        //check that white Qrook position has white Qrook && firstmove
                    }else{
                        //check that black king position has black king && firstmove
                        //check that black Qrook position has black Qrook && firstmove
                    }
                    continue;
                }
            }
            input = convertcoords(ctable.numtable, ctable.chartable, rawinput);

            char promotedPiece = '\0';
            if(gameboard.piececheck(input, turn)){
                if(gameboard.movecheck(input)){
                    if(!gameboard.pincheck(input,turn)){
                        if(gameboard.board[input.first.first][input.first.second]->symbol == 'p' &&
                        (input.second.first == 0 || input.second.first == 7)){
                            cout << "Enter the promoted piece type (Q,B,N,R): ";
                            cin >> promotedPiece;
                        }
                        gameboard.move(input,promotedPiece);
                    }else{
                        cout <<"move will put king in check" << endl;
                        continue;
                    }
                }else{
                    cout << "invalid move" << endl;
                    continue;
                }
            }else{
                cout << "invalid piece" << endl;
                continue;
            }
            gameboard.printboard();
            if(turn == White){cout << "Black's Turn" << endl; turn = Black;}
            else{cout << "White's turn" << endl; turn = White;}
        }
        //-------------------------
        return winner;
    }
};