#include <iostream>
#include <string>

inline void count(const std::string &s){
    int words = 0, characters = 0;
    auto end = s.end();
    for(auto itr = s.begin(); itr != end; itr++){
        characters++;
        if(*itr == ' ' && itr != end - 1 && *(itr + 1) != ' ')
            words++;
    }
    /* for loop does not count the first word(if any) in string
       if for loop computes one or more words in string, increment the words variable to account for the first word in the string.
       else if no word is found, it means string is either empty or only contains blank characters
    */
    if(words)
        words++;
    std::cout << "Words: " << words << " Characters: " << characters; //You can also use s.size() instead of counting characters
}

int main()
{
    std::string s;
    getline(std::cin, s);
    count(s);
}