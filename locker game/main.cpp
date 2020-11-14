#include <iostream>

using namespace std;

int main()
{
    int i,n,j,l,number;
    l=0;
    cout<<"enter number of lockers ";
    cin>> number;
    number++;
    bool locker[number];

    for (n=1;n<number;++n)
    {
        locker[n]=0;

    }

    for (i=1;i<number;++i)
    {

        for(j=1;j<number;++j)
        {
            l=i*j;
            if(l<number)
         {
             locker[l]=!locker[l];
         }

         }
    }

     for (n=1;n<number;++n)
    {
        if(locker[n]==1)
        cout<<"locker no "<< n <<" is open "<<endl;

    }
    return 0;
}
