/*
========================================================================================================
Name : 8.c
Author : Prajyot Shende
Description : Write a separate program using signal system call to catch the signal SIGFPE.
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
	
	signal(SIGFPE, sig);
	int a = 1/0; 
        
}

/*
========================================================================================================
Output:

./a.out
Floating point exception


========================================================================================================
*/
