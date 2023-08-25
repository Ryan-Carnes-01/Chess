#include "includes.h"
pair <pair<int,int>,pair<int,int>> convertcoords(int numtable[9],int chartable[256], pair <pair<unsigned char,int>,pair<unsigned char,int>> playerinput){
    pair <pair<int,int>,pair<int,int>> rvalue;

    rvalue.first.first = numtable[playerinput.first.second];
    rvalue.second.first = numtable[playerinput.second.second];
    rvalue.first.second = chartable[playerinput.first.first];
    rvalue.second.second = chartable[playerinput.second.first];
    
    //conversion table: use playerinput to index into arrays that contain wanted values
    return rvalue;
}
pair <pair<unsigned char,int>,pair<unsigned char,int>> playerinput(){
    //REDO this function. Take in a string and parse it instead of directly inputting coords
    pair <pair<unsigned char,int>, pair<unsigned char,int>> retvalue;
    pair<unsigned char,int> piece_coords;
    pair<unsigned char,int> move_coords;
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