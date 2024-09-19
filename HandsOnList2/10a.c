/*
========================================================================================================
Name : 10.a
Author : Prajyot Shende
Description : Write a separate program using sigaction system call to catch the signal SIGSEGV.
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

	struct sigaction a;
    	a.sa_handler = sig;
    	sigemptyset(&a.sa_mask);
    	



        sigaction(SIGSEGV,&a,0);
        
        int *ptr = NULL;
        *ptr = 1000000;


        //getchar();

        //trigger_segfault();

}

/*
========================================================================================================
Output:

./a.out
Segmentation Fault Discovered


========================================================================================================
*/
