#include <iostream>
#include <stdexcept>

using namespace std;

int main()
{
    int a, b;
    bool success = false;
    while(!success){
        cin >> a >> b;
        try{
            if( b == 0)
                throw runtime_error("Can't divide by zero. Try Again");
            success = true;
        }catch(runtime_error err){
            cout << err.what() << endl;
            success = false;
        }
    }
    cout << a/b;
}