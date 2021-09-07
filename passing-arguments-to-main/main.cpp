#include <iostream>

using namespace std;

int main(int argc, char **argv)  //same as int main(int argc, char **argv)
{
    cout << "Program name: " << argv[0] << endl;
    cout << "Arguments passed: ";
    for(int i = 1; i < argc; i++){
        cout << argv[i] << " ";
    }
    cout << endl;
    return 0;
}