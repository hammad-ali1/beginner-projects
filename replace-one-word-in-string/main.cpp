#include <iostream>
#include <string>

using namespace std;

void replace_word(string &word, const string &search, const string &replace){
    auto found = word.find(search); //Index of keyword to be replaced
    if(found == string::npos){ //Keyword not found
        cout << "Error! keyoword: " << search << " is not present in string: " << word << endl;
    }else{
        auto found_end = found + search.length(); //Index of character after the end of keyword
        if(found_end == word.length() || word[found_end] == ' '){ //Verify if keyword is an exact word in the string
            word.replace(found, found_end - found, replace ); 
        }else{
            cout << "Warning! keyword: " << search << " does not match an exact word in string: " << word << endl;
            cout << "Press Y to still replace keyword in string";
            string choice;
            cin >> choice;
            if(choice == "Y" || choice == "y")
                word.replace(found, found_end - found, replace );
        }
    }
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