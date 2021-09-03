#include <iostream>
#include <string>
#include "board.h"

int main(){
    Board board;
    int num, player = 1;
    cout << endl << "Player " << player << " turn:  ";
    while( cin >> num ){
        switch(player){
            case 1:
                board.input(num, "O");
                player = 2;
                break;
            case 2:
                board.input(num, "X");
                player = 1;
                break;
        }
        board.display();
        if(board.check())
            break;
        cout << endl << "Player " << player << " turn:  ";
    }
}