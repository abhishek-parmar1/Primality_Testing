// program to store the prime numbers in a file
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<time.h>
#define max 1000000	
int isPrime()
{
	FILE *f;
	
	f=fopen("abhiPrime.txt","w");
	unsigned int i,k=0,j,c;
	
	for(i=0;i<max;i++){
		
		// if number is 2 then it is prime
		if(i==2)
		{
			k++;
			fprintf(f,"1 %d\t",i);
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
				fprintf(f,"%d %d\t",k,i);
				
				if(k%10==0)
					fprintf(f,"\n");
				
				if(k%100==0)
					fprintf(f,"\n");
				
				if(k==10000)
					break;
			}
						
		}
	}
	
	printf("%d",k);
	
	fclose(f);
	
}

int main()
{
	clock_t ti;
	
	ti=clock();
	isPrime();
	ti=clock()-ti;
	
	double total=((double)ti)/CLOCKS_PER_SEC;
	printf("\n%lf",total);
	
	return 0;
}
