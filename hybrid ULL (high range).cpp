// hybrid program
#include <iostream>
#include <stdio.h>	
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <map>
#include <vector>
#include <list>
typedef unsigned long long int ULL;
using namespace std;

// map to store prime factors of a number with their powers
map< ULL, ULL> factors;
map< ULL, ULL> :: iterator itr;

// function to store the factors in the map and their powers
void createMap(ULL n)
{
	if(factors.find(n) == factors.end())
		factors[n]=1;
	else
		factors[n]++;
}

// function to store prime factors of a number in the map
void primeFactors(ULL n)
{
	// divide the number by 2 untill it bcomes the odd number
	while (n%2==0)
	{
		createMap(2);
		n = n/2;
	}

	// find the prime factors of a number which are from 3 onwards 
	for (ULL i=3; i*i<=n; i=i+2)
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
	ULL sum=1;
	for( itr=factors.begin(); itr!=factors.end(); itr++)
	{
		sum = sum * ( (pow(itr->first,itr->second+1)-1)/(itr->first-1) );
	}
	cout<<"sum of divisors : "<<sum<<"\n";
}

// function to get the divisors of a number using prime factors of a number
void getDivisors( ULL row_size)
{
	// dimensions of 2D array 
	row_size += 1;
	ULL total_row = factors.size();
	
	// 2D array created
	ULL ** a = new ULL*[total_row];
	for ( int i=0; i<total_row; i++)
	{
		a[i] = new ULL[row_size];
		fill_n(a[i],row_size,0);
	}
	
	// to store the powers of prime factors in the 2D array
	ULL row=0;
	for( itr=factors.begin(); itr!=factors.end(); itr++)
	{
		for( ULL j=0; j<=itr->second; j++)
		{
			a[row][j] = pow(itr->first,j);
		}
		row++;
	}
	
	// create a temp vector of size = row_size with  each element is 1
	vector<ULL> temp(row_size,1);
	// final output vector
	vector<ULL> divisors;
	vector<ULL> :: iterator itr1;
	
	// perform operations on the 2D matrix to get all the divisors of the number  
	for(ULL i=0; i<total_row; i++)
	{
		for(ULL j=0; j<row_size; j++)
		{
			for(ULL k=0; k<temp.size(); k++)
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
	//cout<<"divisors are : \n";
	//for(ULL i=0;i<divisors.size();i++)
	//	cout<<divisors.at(i)<<" ";
	// display count of the divisors of the number
	cout<<"\ncount of divisors : "<<divisors.size();	
}

// function to get the count of numbers less than n and relative prime to it
void eulersFunction()
{
	ULL count=1;
	for( itr=factors.begin(); itr!=factors.end(); itr++)
	{
		count = count * ( (pow(itr->first,itr->second-1))*(itr->first-1) );
	}
	cout<<"\ncount of number less than number and relative prime to it : "<<count<<"\n";
}

// function to get the euler set elements 
void getEulerElements(ULL n)
{
	// final output list
	list<ULL> reduced_residue_set;
	// non relative prime list
	list<ULL> non_relative_prime;
	list<ULL> :: iterator itr2;
	
	// store the numbers from 2 to n-1 in the output list  
	for(ULL i=2; i<n; i++)
		reduced_residue_set.push_back(i);
	
	// store the number which are multiples of prime factors of n and less than n in the non_relative_prime
	for(itr=factors.begin(); itr!=factors.end(); itr++)
	{
		ULL temp=itr->first;
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
	
	// display the elements of the reduced_residue_set
	for(itr2=reduced_residue_set.begin(); itr2!=reduced_residue_set.end(); itr2++)
		cout<<*itr2<<" ";
	// display size of reduced_residue_set
	cout<<"\ncount (for verification) : "<<reduced_residue_set.size();
}

int main()
{
	ULL n,max_power=0;
	
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
	
	// get euler set elements ( cannot be called  because of very big number)
	//getEulerElements(n);
	
	return 0;
}

