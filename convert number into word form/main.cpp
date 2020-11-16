#include <iostream>
#include<conio.h>
using namespace std;

int main()
{
    int n,second_digit,first_digit;
    cout<<"enter number ";
    cin>>n;
    string words[]={"zero","one","two","three","four","five","six","seven","eight","nine","ten","eleven","twelve","thirteen","fourteen",
    "fifteen","sixteen","seventeen","eighteen","nineteen","twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};
    second_digit=n%10;
    n=n/10;
    first_digit=n%10;
    if (first_digit==1||first_digit==0){
        cout<<words[10*first_digit+second_digit];
    }
    if (first_digit>1&&second_digit!=0){
        cout<<words[18+first_digit]<<" "<<words[second_digit];
    }
    if (first_digit>1&&second_digit==0){
            cout<<words[18+first_digit];
    }
    getch();
    return 0;
}
