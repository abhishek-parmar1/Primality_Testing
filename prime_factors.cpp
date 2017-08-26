// hybrid wap
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <map>
#include <vector>
#include <list>

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
	
	// to remove the 0 form the divisors list if present
	if(divisors.at(0) == 0)
		divisors.assign(divisors.begin()+1, divisors.end());
	
	// display the divisors of the number
	cout<<"divisors are : \n";
	for(int i=0;i<divisors.size();i++)
		cout<<divisors.at(i)<<" ";
	// display count of the divisors of the number
	cout<<"\ncount of divisors : "<<divisors.size();	
}

// function to get the count of numbers less than n and relative prime to it
void eulersFunction()
{
	int count=1;
	for( itr=factors.begin(); itr!=factors.end(); itr++)
	{
		count = count * ( (pow(itr->first,itr->second-1))*(itr->first-1) );
	}
	cout<<"\ncount of number less than number and relative prime to it : "<<count<<"\n";
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
	
	// store the multiples of the elements which divides the n in non_relative_prime list 
	for(itr2=reduced_residue_set.begin(); itr2!=reduced_residue_set.end(); itr2++)
		{
			int temp1=*itr2,temp2;
			if(n%temp1==0)
			{
				temp2=temp1;
				while(temp2<n)
				{
					non_relative_prime.push_back(temp2);
					temp2+=temp1;
				}	
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
	
	// display the elements of the reduced_residue_set
	for(itr2=reduced_residue_set.begin(); itr2!=reduced_residue_set.end(); itr2++)
		cout<<*itr2<<" ";
	// display size of reduced_residue_set
	cout<<"\ncount (for verification) : "<<reduced_residue_set.size();
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
	
	// get the divisors of a number using prime factors of a number 
	getDivisors(max_power);
	
	// get the count of numbers less than n and relative prime to it
	eulersFunction();
	
	// get euler set elements
	getEulerElements(n);
	
	return 0;
}

