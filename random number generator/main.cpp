#include <iostream>
#include<cstdlib>
#include <ctime>
#include <conio.h>
using namespace std;

int main()
{

     srand(time(0));
     cout<<"random number generator seed is "<<time(0);
   for (int x=0;x<15;x++)
   {
       cout<<endl<< rand() % 100;
   }
   getch();
    return 0;
}
