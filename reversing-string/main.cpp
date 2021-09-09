#include <iostream>
#include <string>

using namespace std;

inline const string& reverse(string & s){
    auto end = s.end();
    for(auto beg = s.begin(); beg != end; beg++){
        end--;
        char temp = *beg;
        *beg = *end;
        *end = temp;
    }
    return s;
}

int main()
{
    string s;
    cin >> s;
    cout << reverse(s);
}