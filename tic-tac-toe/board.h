#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Board{
    public:
        Board() : boxValue(9, " "), rows{0, 3, 6}, columns{0, 1, 2}, moves(0){
            display();
        }
        void display(){
            int num = 0;
            system("cls");
            cout << "PLAYER ONE O ; PLAYER TWO X\n\n";
            cout << " --- --- ---\n";
            cout << "| " << boxValue[num++] << " " << "|" << " " << boxValue[num++] << " " << "|" << " " << boxValue[num++] << " " << "|" << endl;
            cout << " --- --- ---\n";
            cout << "| " << boxValue[num++] << " " << "|" << " " << boxValue[num++] << " " << "|" << " " << boxValue[num++] << " " << "|" << endl;
            cout << " --- --- ---\n";
            cout << "| " << boxValue[num++] << " " << "|" << " " << boxValue[num++] << " " << "|" << " " << boxValue[num++] << " " << "|" << endl;
            cout << " --- --- ---\n";
        }
        void input(unsigned int numArg, string mark){
            //VALIDATE INPUT
            while(numArg > 8 || boxValue[numArg] != " "){
                cout << endl << "ERROR POSITION NOT VALID. TRY AGAIN:  ";
                cin >> numArg;
            }
            moves++; //COUNT MOVES 
            boxValue[numArg] = mark; 
            display();
            //CHECK IF ANY PLAYER WON OR MATCH IS TIE
            if(check()){
                if(mark == "X")
                    cout << endl << "PLAYER TWO WON" << endl;
                else
                    cout << endl << "PLAYER ONE WON" << endl;
                exit(1);
            }else if(moves == 9){
                cout << "\nTIE\n";
                exit(1);
            }
        }
        bool check(){
            bool win = false;
            for( auto x : rows){
                if(win = checkRow(x))
                    return win;
            }
            for( auto y : columns){
                if(win = checkColumn(y))
                    return win;
            }
            if(boxValue[2] != " " && (win = boxValue[2] == boxValue[4] && boxValue[2] == boxValue[6]) )
                return win;
            if(boxValue[0] != " " && (win = boxValue[0] == boxValue[4] && boxValue[0] == boxValue[8]) )
                return win;
            return win;
        }
    private:
        vector<int> rows;
        vector<int> columns;
        vector<string> boxValue;
        int moves;
        bool checkRow(const int &row){
            if(boxValue[row] == " ")
                return false;
            else
                return ( boxValue[row] == boxValue[row + 1] &&
                        boxValue[row] == boxValue[row + 2] );
        }
        bool checkColumn(const int &column){
            if(boxValue[column] == " ")
                return false;
            else
                return ( boxValue[column] == boxValue[column + 3] &&
                        boxValue[column] == boxValue[column + 6] );
        }
};