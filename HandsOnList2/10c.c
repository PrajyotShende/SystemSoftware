/*
========================================================================================================
Name : 10.c
Author : Prajyot Shende
Description : Write a separate program using sigaction system call to catch the following signals.
		c. SIGFPE
Date: 12 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<signal.h>
#include<stdlib.h>


void sig()
{
        printf("\n");
        printf("Floating point exception\n");
        exit(1);
}


int main()
{    
	
	struct sigaction a;
        a.sa_handler = sig;
        sigemptyset(&a.sa_mask);

        sigaction(SIGFPE,&a,0);
	
	int z = 1/0; 
}

/*
========================================================================================================
Output:

./a.out
Floating point exception


========================================================================================================
*/
