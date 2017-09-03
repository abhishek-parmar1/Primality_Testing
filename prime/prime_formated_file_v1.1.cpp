// program to store the prime numbers in a file
#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<map>
#define max 1000000

using namespace  std;

map<int,int> prime_map;
map<int,int> :: iterator itr;
	
int isPrime()
{
	unsigned int i,k=0,j,c;
	
	for(i=0;i<max;i++){
		
		// if number is 2 then it is prime
		if(i==2)
		{
			k++;
			prime_map[1]=i;
		}
		
		// if number is divisible by 2 then not prime
		else if(i%2==0 || i==1)
			continue;
		
		// if number is odd then check its is prime or not using a loop
		else
		{
			c=0;
			// check number is prime or not
			for(j=3;j*j<=i;j=j+2)
			{
				if(i%j==0)
				{
					c=1;
					break;
				}
			}
			// if prime write the number to the file
			if(c==0)
			{
				k++;
				prime_map[k]=i;
				if(k==10000)
					break;
			}
						
		}
	}
	
	printf("%d\n",k);
	
}

int main()
{
	isPrime();
	FILE *f;
	f=fopen("Prime.html","w");
	int c=0;
	for(int i=1;i<=10000;i++)
	{
		for(int j=1;j<=5;j++)
		{
			fprintf(f,"<b>%d</b>&nbsp; : &nbsp;%d&nbsp;&nbsp;&nbsp;&nbsp;",i+c,prime_map[i+c]);
			c+=10;	
		}
		if(i%10==0)
		{
			fprintf(f,"<br>");
			i+=40;
		}
		fprintf(f,"<br>");
		c=0;
	}
	fclose(f);
	
	return 0;
}
