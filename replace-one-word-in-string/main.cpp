#include <iostream>
#include <string>

using namespace std;

void replace_word(string &word, const string &search, const string &replace){
    auto found = word.find(search); //Index of keyword to be replaced
    if(found == string::npos){ //Keyword not found
        cout << "Error! keyoword: " << search << " not present in string: " << word << endl;
    }else{
        auto found_end = found + search.length();//Index of character after the end of keyword
        word.replace(found, found_end - found, replace );
    }
}

int main()
{
    string s("Hi my name is Hammad Ali");
    replace_word(s, "Ali", "Muhammad");
    cout << s << endl;
}