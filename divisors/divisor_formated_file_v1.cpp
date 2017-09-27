/* wap for : 
            1> count of divisros 
            2> sum of all divisors
            3> list all divisors 
                                 of all numbers 
*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <map>
#include <vector>

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

// function to get sum of divisors of a number
void divisorsSum()
{
	int sum=1;
	for( itr=factors.begin(); itr!=factors.end(); itr++)
	{
		sum = sum * ( (pow(itr->first,itr->second+1)-1)/(itr->first-1) );
	}
	fprintf(f,"<td>%d&nbsp;&nbsp;&nbsp;</td>",sum);
}

// function to get the divisors of a number using prime factors of a number
void getDivisors( int row_size)
{
	// dimensions of 2D array 
	row_size += 1;
	int total_row = factors.size();
	
	// 2D array created
	int ** a = new int*[total_row];
	for ( int i=0; i<total_row; i++)
	{
		a[i] = new int[row_size];
		fill_n(a[i],row_size,0);
	}
	
	// to store the powers of prime factors in the 2D array
	int row=0;
	for( itr=factors.begin(); itr!=factors.end(); itr++)
	{
		for( int j=0; j<=itr->second; j++)
		{
			a[row][j] = pow(itr->first,j);
		}
		row++;
	}
	
	// create a temp vector of size = row_size with  each element is 1
	vector<int> temp(row_size,1);
	// final output vector
	vector<int> divisors;
	vector<int> :: iterator itr1;
	
	// perform operations on the 2D matrix to get all the divisors of the number  
	for(int i=0; i<total_row; i++)
	{
		for(int j=0; j<row_size; j++)
		{
			for(int k=0; k<temp.size(); k++)
			{
				divisors.push_back(a[i][j]*temp.at(k));			
			}
		}
		// sort and remove the duplicates from the vector
		sort(divisors.begin(),divisors.end());
		divisors.erase( unique( divisors.begin(), divisors.end()), divisors.end());
		// clear the previous vector
		temp.clear();
		// store the resulted vector in temp vector
		temp.assign(divisors.begin(),divisors.end());		
	}
	
	// to remove the 0 form the divisors list if present
	if(divisors.at(0) == 0)
		divisors.assign(divisors.begin()+1, divisors.end());
	
	// display count of the divisors of the number
	fprintf(f,"<td>%d&nbsp;&nbsp;&nbsp;</td>",divisors.size());
	
	// for sum of divisors of a number
	divisorsSum();
	
	fprintf(f,"<td>");
	// display the divisors of the number
	for(int i=0;i<divisors.size();i++)
		fprintf(f,"%d, ",divisors.at(i));
	fprintf(f,"</td>");	
}

int main()
{
	int max_power=0;
	
	f=fopen("divisor.html","w");
	fprintf(f,"<table border='2px'>");
	fprintf(f,"<thead><tr align='center'><td><b>NUMBERS</b></td><td><b>COUNT OF DIVISORS</b></td><td><b>SUM OF DIVISORS</b></td><td><b>DIVISORS</b></td></tr></thead>");
	for(int i=2;i<=10000;i++)
	{
		fprintf(f,"<tr>");
		fprintf(f,"<td><b>%d</b>&nbsp;&nbsp;&nbsp;</td>",i);	
		max_power=0;
		
		// get the prime factors of a number
		primeFactors(i);
		
		// get the maximum power
		for( itr=factors.begin(); itr!=factors.end(); itr++)
		{
			if(itr->second > max_power)
				max_power = itr->second;
		}
		
		// get the divisors of a number using prime factors of a number 
		getDivisors(max_power);	
		
		// reset the map 
		factors.clear();
		fprintf(f,"</tr>");
	}
	fprintf(f,"</table>");
	fclose(f);
	
	return 0;
}

