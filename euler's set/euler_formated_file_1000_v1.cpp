/* wap for : 
            1> count of relative prime 
            2> list all the relative primes 
                                           of all numbers 
*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <map>
#include <list>

using namespace std;

// map to store prime factors of a number with their powers
map< int, int> factors;
map< int, int> :: iterator itr;
FILE *f;

// function to store the factors in the map and their powers
void createMap(int n)
{
	if(factors.find(n) == factors.end())
		factors[n]=1;
	else
		factors[n]++;
}

// function to store prime factors of a number in the map
void primeFactors(int n)
{
	// divide the number by 2 untill it bcomes the odd number
	while (n%2==0)
	{
		createMap(2);
		n = n/2;
	}

	// find the prime factors of a number which are from 3 onwards 
	for (int i=3; i*i<=n; i=i+2)
	{
		while (n%i==0)
		{
			createMap(i);
			n = n/i;
		}
	}

	// number left with no factors 
	if (n>2)
		createMap(n);
		
}

// function to get the count of numbers less than n and relative prime to it
void eulersFunction()
{
	int count=1;
	for( itr=factors.begin(); itr!=factors.end(); itr++)
	{
		count = count * ( (pow(itr->first,itr->second-1))*(itr->first-1) );
	}
	fprintf(f,"<td>%d&nbsp;&nbsp;</td>",count);
}

// function to get the euler set elements 
void getEulerElements(int n)
{
	// final output list
	list<int> reduced_residue_set;
	// non relative prime list
	list<int> non_relative_prime;
	list<int> :: iterator itr2;
	
	// store the numbers from 2 to n-1 in the output list  
	for(int i=2; i<n; i++)
		reduced_residue_set.push_back(i);
	
	// store the number which are multiples of prime factors of n and less than n in the non_relative_prime
	for(itr=factors.begin(); itr!=factors.end(); itr++)
	{
		int temp=itr->first;
		while(temp<n)
		{
			non_relative_prime.push_back(temp);
			temp+=itr->first;
		}
	}
	
	// to remove the duplicates from the non_relative_prime list
	non_relative_prime.sort();
	non_relative_prime.unique();
	
	// remove the non_relative_prime from the reduced_residue_set
	for(itr2=non_relative_prime.begin(); itr2!=non_relative_prime.end(); itr2++)
		reduced_residue_set.remove(*itr2);

	// insert 1 in the reduced_residue_set
	reduced_residue_set.push_front(1);
	
	fprintf(f,"<td>");
	// display the elements of the reduced_residue_set
	for(itr2=reduced_residue_set.begin(); itr2!=reduced_residue_set.end(); itr2++)
		fprintf(f,"%d, ",*itr2);
	fprintf(f,"</td>");
}

int main()
{
	f=fopen("euler.html","w");
	
	fprintf(f,"<table border='2px'>");
	fprintf(f,"<thead><tr align='center'><td><b>NUMBERS</b></td><td><b>EULER's COUNT</b></td><td><b>EULER's SET</b></td></tr></thead>");
	for(int i=1;i<=1000;i++)
	{
		fprintf(f,"<tr>");
		
		fprintf(f,"<td><b>%d</b>&nbsp;&nbsp;</td>",i);
		
		primeFactors(i);
		
		// get the euler count of a number
		eulersFunction();
		
		// get the euler set by using prime factoors of a number
		getEulerElements(i);	
		
		// reset the map 
		factors.clear();
		fprintf(f,"</tr>");
	}
	fprintf(f,"</table>");
	
	fclose(f);
	return 0;
}

