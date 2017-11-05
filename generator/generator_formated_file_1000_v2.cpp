#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<algorithm>
#include<list>
#include<map>
#include<math.h>

using namespace std;

typedef unsigned long long int ULL;
// map to store the powers
map<ULL, ULL> powers;
map<ULL, ULL> :: iterator itr;

// check whether number is prime or not
int primeOrNot(ULL n)
{
	if(n==2)
		return 1;
	if(n%2==0 || n==1)
		return 0;
	else
	{
		for(ULL i=3; i*i<=n; i+=2)
		{
			if(n%i==0)
				return 0;
		}
		return 1;
	}
}

// find first generator and store its powers
int firstGenerator(ULL n,ULL p)
{
	powers.clear();
	ULL i;
	ULL r = 1%p;
	for(i=1; i<p; i++)
	{
		r=(r*n)%p;
		powers[i]=r;
		if(r==1)
			break;	
	}	
	if(i==p-1)
		return 1;
	else
		return 0;
}

int main()
{
	ULL n;
	FILE *f;
	
	f=fopen("primitive_root_v2.1.html","w");
	fprintf(f,"<table border='2px'>");
	fprintf(f,"<thead> <tr align='center'> <td><b>Prime Numbers</b></td> <td><b>Smallest Generator</b></td> <td><b>power with 10 remainder</b></td> <td><b>inverse of 10</b></td> </tr> </thead>");
	
	for(n=11; n<=10000; n++)
	{
		
		ULL first_gen=0;
		//  check n prime or not
		if(!primeOrNot(n))
		{
			continue;
		}
		
		// find first generator
		for(ULL i=2; i<n; i++)
		{
			if(firstGenerator(i,n))
			{
				first_gen=i;
				break;
			}
		}
		
		fprintf(f,"<tr>");
		fprintf(f,"<td>%llu</td>",n);
		fprintf(f,"<td>%llu</td>",first_gen);
		ULL t1;
		for(itr=powers.begin(); itr!=powers.end(); itr++)
		{
			if(itr->second==10)
				{
					t1=itr->first;
					break;
				}
		}
		fprintf(f,"<td>%llu</td>",t1);
		long long int temp1=powers[n-1-t1];
		long long int temp2=n;
		if(temp1>(n/2))
		{
			temp1=temp1-temp2;
			fprintf(f,"<td>%lld</td>",temp1);
		}	
		else
			fprintf(f,"<td>%llu</td>",powers[n-1-t1]);	
		fprintf(f,"</tr>");

	}
	fprintf(f,"</table>");
	fclose(f);
	return 0;
}
