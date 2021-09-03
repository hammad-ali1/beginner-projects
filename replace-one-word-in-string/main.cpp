#include <iostream>
#include <string>

using namespace std;

void replace_word(string &word, const string &search, const string &replace){
    size_t found, found_end, start = 0;
    do{
        found = word.find(search, start); //Index of keyword to be replaced
        if(found == string::npos){ //Keyword not found
            cout << "Error! keyoword: " << search << " does not match an exact word in string: " << word << endl;
            return;
        }else{
            found_end = found + search.length(); //Index of character after the end of keyword
        }
        start = found_end;
        //Keep looping untill a word exactly matches with keyword
        /* Loop ends in following conditions
           1) Index of keyword is zero i.e (found = 0) OR Character before the index(found) is a whitespace
           AND
           2) Index of keyword is the length of string i.e (found = word.length()) OR Character after the index(found) is a whitespace
        */
    }while( !(( found == 0 || word[found - 1] == ' ') && (found_end == word.length() || word[found_end] == ' ')) );
    word.replace(found, found_end - found, replace ); 
}

int main()
{
    string s("Hi my name is Hammad Ali");
    cout << "string is: " << s;
    string keyword, replaced;
    cout << "\nEnter word to be replaced and word to replace it with: " << endl;
    while(cin >> keyword >> replaced){
    replace_word(s, keyword, replaced);
    cout << "\nNew string: \n" << s << endl;
    }
}