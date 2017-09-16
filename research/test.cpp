#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef unsigned long long int ULL;

using namespace std;
 
int primeOrNot(ULL n )
{
	if(n==2)
        return 1;
    if(n%2==0)
        return 0;
    int flag=0;
    ULL i=3;
    while(i*i<=n)
    {
    	if(n%i==0)
		{
    		flag=1;
            break;
		}    
        i+=2;
	}
    if(flag==0)
        return 1;
    else
        return 0;
}
 
ULL calculate(ULL i,ULL d)
{
	ULL r=70368744177664%d;
	ULL j;
    for(j=48; j<i; j+=2)
       r= (r*4)%d;
    return r;
} 
 
int main()
{
	//34173511
	for(ULL i=34173511; i<=300000000; i++)
	{
		if(primeOrNot(i)==1)
		{
			cout<<i<<"\n";
        	ULL d=i*i;
        	ULL p=calculate(i,d);
        	if(p==1)
        	{
        		cout<<"number is : "<<i<<"\n";	
        		break;
			}
		}
	}
	cout<<"did not get any thing";
}
