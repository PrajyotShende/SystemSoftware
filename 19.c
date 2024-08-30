/*
========================================================================================================

Name: 19
Author: Prajyot Shende
Description: Write a program to find out time taken to execute getpid system call. Use time stamp counter.
Date: 29th August, 2024

========================================================================================================
*/

#include <stdio.h>
#include <time.h>
#include <unistd.h>

unsigned long rdtsc ()
	{
    		unsigned long dst;
   	 	__asm__ __volatile__("rdtsc": "=A"(dst));
    		return dst;
	}
int main()
{
	int nano_sec;
	long int l,r;
	l = rdtsc();
	printf("ID of the process is %d\n", getpid());
	int i=0;
	while((i++)<100) getppid();
	r = rdtsc();
	nano_sec = (r-l)/4.7;
	printf("The Used Fnct takes %d nano seconds to execute",nano_sec);
}
	

/*
========================================================================================================
Output:

/a.out
ID of the process is 11374
The Used Fnct takes 42349 nano seconds to execute


========================================================================================================
*/
