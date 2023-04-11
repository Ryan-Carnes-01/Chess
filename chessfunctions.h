#include "includes.h"


pair <pair<int,int>,pair<int,int>> convertcoords(int numtable[9],int chartable[256], pair <pair<char,int>,pair<char,int>> playerinput){
    //chessnotation->arraynotation TODO 
//    cout << playerinput.first.first << playerinput.first.second << " " << playerinput.second.first << playerinput.second.second << "\n";
    pair <pair<int,int>,pair<int,int>> rvalue;
    rvalue.first.first = playerinput.first.second; //num
    rvalue.first.second = playerinput.first.first; //char
    rvalue.second.first = playerinput.second.second; //num
    rvalue.second.second = playerinput.second.first; //char

//    cout << rvalue.first.first << rvalue.first.second << " " << rvalue.second.first << rvalue.second.second << "\n";
    
    rvalue.first.first = numtable[rvalue.first.first];
    rvalue.second.first = numtable[rvalue.second.first];
    rvalue.first.second = chartable[rvalue.first.second];
    rvalue.second.second = chartable[rvalue.second.second];
    //conversion table: use rvalues to index into arrays that contain wanted values
//    cout << rvalue.first.first << rvalue.first.second << " " << rvalue.second.first << rvalue.second.second << "\n";
    return rvalue;
}
pair <pair<char,int>,pair<char,int>> playerinput(){
    pair <pair<char,int>, pair<char,int>> rvalue;
    pair<char,int> piece_coords;
    pair<char,int> move_coords;
    cin >> piece_coords.first >> piece_coords.second;
    cout << "--to->\n";
    cin >> move_coords.first >> move_coords.second;
    cout << piece_coords.first << piece_coords.second << "->" << move_coords.first << move_coords.second << '\n';
    rvalue.first = piece_coords; rvalue.second = move_coords;
    return rvalue;
}
