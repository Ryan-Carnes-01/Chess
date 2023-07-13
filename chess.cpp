#include "chess.h"

int main(){
    Chess Game;
    Team winner;
    Game.printgreeting();
    winner = Game.run();
    if(winner == White){
        cout << "White wins!" << endl;
    }else{cout << "Black wins!" << endl;}
    return 0;
}