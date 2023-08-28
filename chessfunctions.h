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
void parseinput(string input,pair<unsigned char, int>*piece_coords,pair<unsigned char,int>*move_coords){
    if(input == "help" || input == "Help" || input == "HELP"){
        cout << endl <<"Examples of valid movement input options:" << endl << "e2 e4" << endl << "e2 -> e4" << endl << "e2 to e4" << endl << endl;
        cout << "Type 'quit' to exit the program" << endl << "Type 'castle' to castle your king" << endl << "Try your input again:" << endl << endl;
        piece_coords->first = 'z'; 
        piece_coords->second = -1;
        move_coords->first = 'z';
        move_coords->second = -1;
    }
    else if(input == "quit" || input == "Quit" || input == "QUIT"){
        exit(1);
    }
    else if(input == "castle" || input == "Castle" || input == "CASTLE"){
        cout << "Kingside or Queenside?" << endl;
        int flag = 1;
        while(flag){
            cin >> input;
            if(input == "Kingside" || input == "kingside" || input == "KINGSIDE" || input == "K" || input == "King" || input == "k"){
                piece_coords->first = 'k'; 
                piece_coords->second = -1;
                move_coords->first = 'k';
                move_coords->second = -1;
                flag = 0;
            }else if(input == "Queenside" || input == "queenside" || input == "QUEENSIDE" || input == "Q" || input == "Queen" || input == "q"){
                piece_coords->first = 'q'; 
                piece_coords->second = -1;
                move_coords->first = 'q';
                move_coords->second = -1;
                flag = 0;
            }else{
                cout << "Invalid castling input, try again" << endl;
            }
        }
    }
    else{//e2 -> e4 //e2 to e4
        if(input.size() == 8 && input[2] == ' ' && input[5] == ' '){
            piece_coords->first = input[0];
            piece_coords->second = input[1] - '0';
            move_coords->first = input[6];
            move_coords->second = input[7] - '0'; 
        }
        //e2 e4
        else if(input.size() == 5 && input[2] == ' '){
            piece_coords->first = input[0];
            piece_coords->second = input[1] - '0';
            move_coords->first = input[3];
            move_coords->second = input[4] - '0';
        }
        else{
            cout << "Invalid input -- type 'help' for input options" << endl;
            piece_coords->first = 'z';
            piece_coords->second = -1;
            move_coords->first = 'z';
            move_coords->second = -1;
        }
    }
    return;
}
pair <pair<unsigned char,int>,pair<unsigned char,int>> playerinput(){
    //read in string, parse to determine behavior, return coordinates
    pair <pair<unsigned char,int>, pair<unsigned char,int>> retvalue;
    pair<unsigned char,int> piece_coords,move_coords;
    string textinput;
    getline(cin >> ws,textinput);
    parseinput(textinput,&piece_coords,&move_coords);
    retvalue.first = piece_coords;
    retvalue.second = move_coords;
    return retvalue;
}

