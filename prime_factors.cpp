// wap to get prime factors of a number
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
	cout<<"sum of divisors : "<<sum<<"\n";
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
	
	// to remove the 0 form the divisors list
	divisors.assign(divisors.begin()+1, divisors.end());
	
	// display the divisors of the number
	for(int i=0;i<divisors.size();i++)
		cout<<divisors.at(i)<<" ";
	// display count of the divisors of the number
	cout<<"\n"<<divisors.size();	
}

// function to get the count of numbers less than n and relative prime to it
void eulersFunction()
{
	int count=1;
	for( itr=factors.begin(); itr!=factors.end(); itr++)
	{
		count = count * ( (pow(itr->first,itr->second-1))*(itr->first-1) );
	}
	cout<<"count of number less than number and relative prime to it : "<<count<<"\n";
}

int main()
{
	int n,max_power=0;
	
	cin>>n;
	
	// get the prime factors of a number
	primeFactors(n);
	
	// print the prime factors of a number and get the maximum power
	cout<<"Prime factors are : \n";
	for( itr=factors.begin(); itr!=factors.end(); itr++)
	{
		if(itr->second > max_power)
			max_power = itr->second;
		cout<<itr->first<<" : "<<itr->second<<"\n";
	}
	
	// for sum of divisors of a number
	divisorsSum();
	
	// get the count of numbers less than n and relative prime to it
	eulersFunction();
	
	// get the divisors of a number using prime factors of a number 
	getDivisors(max_power);
	
	return 0;
}

