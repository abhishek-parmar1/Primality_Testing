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
// map to store prime factors
map<ULL, ULL> prime_factors;
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

//  function to create map for prime factors
void createMap(ULL x)
{
	if(prime_factors.find(x)==prime_factors.end())
			prime_factors[x]=1;
	else
		prime_factors[x]++;
}

// function to find prime factors
void primeFactors(ULL p)
{
	while(p%2==0)
	{
		createMap(2);
		p=p/2;
	}
	
	for(ULL i=3; i*i<=p; i+=2)
	{
		if(p%i==0)
		{
			createMap(i);
			p=p/i;
		}
	}
	
	if (p>2)
		createMap(p);
}

// function to find relative prime of (p-1)
list<ULL> relativePrimes(ULL p)
{
	list<ULL> relative_prime;
	list<ULL> non_relative_prime;
	list<ULL> :: iterator itr1;
	
	primeFactors(p);
	
	cout<<"prime factors of "<<p<<" are : \n";
	for(itr=prime_factors.begin(); itr!=prime_factors.end(); itr++)
	{
		cout<<itr->first<<" : "<<itr->second<<"\n";
	}
	
	for(ULL i=1; i<p; i++)
		relative_prime.push_back(i);
	
	for(itr=prime_factors.begin(); itr!=prime_factors.end(); itr++)
	{
		ULL temp=itr->first;
		while(temp<p)
		{
			non_relative_prime.push_back(temp);
			temp+=itr->first;
		}
	}
	
	non_relative_prime.sort();
	non_relative_prime.unique();
	
	for(itr1=non_relative_prime.begin(); itr1!=non_relative_prime.end(); itr1++)
		relative_prime.remove(*itr1);
	
	return relative_prime;
}

int main()
{
	ULL n,first_gen=0;
	cin>>n;
	
	//  check n pprime or not
	if(!primeOrNot(n))
	{
		cout<<"not a prime number";
		exit(0);
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
	
	list<ULL> relative_prime;
	list<ULL> :: iterator itr1;
	
	//  calculate relative primes of (n-1)
	relative_prime=relativePrimes(n-1);
	
	// store generators
	list<ULL> generators;
	for(itr1 = relative_prime.begin(); itr1!=relative_prime.end(); itr1++)
	{
		generators.push_back(powers[*itr1]);
	}
	
	// display generators
	cout<<" generators are \n";
	for(itr1 = generators.begin(); itr1!=generators.end(); itr1++)
	{
		cout<<*itr1<<" ";
	}
	
	return 0;
}
