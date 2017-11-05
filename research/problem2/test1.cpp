// check if there are prime numbers which satisfies with equation (p-1)! +1 congruent to 0 (mod p^2)
#include<iostream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

typedef unsigned long long int ullg;

int prime(ullg p)
{
    if( p == 2)
        return 1;
    if( p%2 == 0)
        return 0;
    for(ullg i=3; i*i<=p; i+=2)
    {
        if(p%i==0)
            return 0;
    }
    return 1;
}

int checkEquation(ullg p)
{
    ullg ps = p*p;
    ullg pf = 1;
    for(ullg i=1; i<p; i++)
    {
        pf=(pf*i)%ps;
    }

    if(pf==-1 || pf==ps-1)
        return 1;
    else
        return 0;
}

int main()
{

    for(ullg n=200001; n<2000000000; n+=2)
    {
        if(prime(n) ==1 )
        {
            cout<<n<<"\n";
            if( checkEquation(n) ==1 )
            {
                break;
            }
        }
    }
    return 0;
}
