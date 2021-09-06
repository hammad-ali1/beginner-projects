#include <iostream>
#include <vector>

using namespace std;

int add(const int &a,const int &b){
    return a + b;
}
int sub(const int &a,const int &b){
    return a - b;
}
int mul(const int &a,const int &b){
    return a * b;
}
int div(const int &a,const int &b){
    return a / b;
}
int main()
{
    int num1, num2;
    cout << "Enter two numbers: " ;
    cin >> num1 >> num2;
    //METHOD 1: USING decltype ON FUNCTION
    vector< decltype(add)* > vec1 = {add, sub, mul, div}; //vector of pointers to function "int (const int&, const int&)"
    cout << "vec1: Applying arithmetic operations (+, -, *, /).... " << endl ;
    for(auto func : vec1){ //looping through all functions pointed to by vector elements
        cout << func(num1, num2) << endl;
    }
    //METHOD 2: USING decltype ON POINTER TO FUNCTION
    int (*pointer_to_function) (const int &, const int &); //declaring a pointer to function of type int (const int&, const int&) : UNINITIALIZED    
    vector< decltype(pointer_to_function) > vec2 = {add, sub, mul, div}; // equivalent of vec1      
    cout << "vec2: Applying arithmetic operations (+, -, *, /).... " << endl ;
    for(auto func : vec2){ //looping through all functions pointed to by vector elements
        cout << func(num1, num2) << endl;
    }
    //METHOD 3: USING TYPE ALIAS
    typedef int (*type_alias1) (const int &, const int &);
    vector<type_alias1> vec3 = {add, sub, mul, div}; // equivalent of vec1      
    cout << "vec3: Applying arithmetic operations (+, -, *, /).... " << endl ;
    for(auto func : vec3){ //looping through all functions pointed to by vector elements
        cout << func(num1, num2) << endl;
    }
    //METHOD 4: USING TYPE ALIAS
    using type_alias2 = int (*)(const int&, const int&);
    vector<type_alias2> vec4 = {add, sub, mul, div}; // equivalent of vec1      
    cout << "vec4: Applying arithmetic operations (+, -, *, /).... " << endl ;
    for(auto func : vec4){ //looping through all functions pointed to by vector elements
        cout << func(num1, num2) << endl;
    }
}