#include "chess.h"

int main(){
    Chess Game;
    Game.printgreeting();
    if(Game.run() == true){
        Game.printvictory();
    }else{
        Game.printdefeat();
    }
    return 0;
}