#include "includes.h"
pair <pair<int,int>,pair<int,int>> convertcoords(int numtable[9],int chartable[256], pair <pair<char,int>,pair<char,int>> playerinput){
    pair <pair<int,int>,pair<int,int>> rvalue;
    rvalue.first.first = playerinput.first.second; //num
    rvalue.first.second = playerinput.first.first; //char
    rvalue.second.first = playerinput.second.second; //num
    rvalue.second.second = playerinput.second.first; //char
    
    rvalue.first.first = numtable[rvalue.first.first];
    rvalue.second.first = numtable[rvalue.second.first];
    rvalue.first.second = chartable[rvalue.first.second];
    rvalue.second.second = chartable[rvalue.second.second];
    //conversion table: use rvalues to index into arrays that contain wanted values
    return rvalue;
}
pair <pair<char,int>,pair<char,int>> playerinput(){
    //REDO this function. Take in a string and parse it instead of directly inputting coords
    pair <pair<char,int>, pair<char,int>> retvalue;
    pair<char,int> piece_coords;
    pair<char,int> move_coords;
    cin >> piece_coords.first >> piece_coords.second;
    cout << "--to->\n";
    cin >> move_coords.first >> move_coords.second;
    cout << piece_coords.first << piece_coords.second << "->" << move_coords.first << move_coords.second << '\n';
    retvalue.first = piece_coords; retvalue.second = move_coords;
    return retvalue;
}

int parse(string input){

    return 0;
}