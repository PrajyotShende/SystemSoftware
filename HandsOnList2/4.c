/*
========================================================================================================
Name : 4
Author : Prajyot Shende
Description : Write a program to measure how much time is taken to execute 100 getppid() system call. Use time stamp counter.
Date: 12 Sept, 2024.
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
	//printf("ID of the process is %d\n", getpid());
	int i=0;
	while((i++)<100) getppid();
	r = rdtsc();
	nano_sec = (r-l)/4.7;
	printf("The Time taken is %d nano seconds to execute",nano_sec);
}

/*
========================================================================================================
Output:

./a.out
The Time taken is 12993 nano seconds to execute

========================================================================================================
*/
