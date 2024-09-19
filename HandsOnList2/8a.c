/*
========================================================================================================
Name : 8.a
Author : Prajyot Shende
Description : Write a separate program using signal system call to catch the signal SIGSEGV.
Date: 12 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<signal.h>
#include<stdlib.h>


void sig()                      
{
        printf("Segmentation Fault Discovered\n");
        exit(1);
}


int main() 
{
    	signal(SIGSEGV, sig);


	int *ptr = NULL;
        *ptr = 1000000;






}

/*
========================================================================================================
Output:

./a.out
Segmentation Fault Discovered


========================================================================================================
*/
