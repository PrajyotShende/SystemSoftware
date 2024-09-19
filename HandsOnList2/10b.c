/*
========================================================================================================
Name : 10.b
Author : Prajyot Shende
Description : Write a separate program using sigaction system call to catch the following signals.
		b. SIGINT
Date: 12 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<signal.h>
#include<stdlib.h>


void sig()
{
	printf("\n");
        printf("Interrupt signal wasdetected \n");
        exit(1);
}


int main()
{
	printf("When terminating a process on terminal by using ctrl + c you will get a interrupt signal\n");

        struct sigaction a;
        a.sa_handler = sig;
        sigemptyset(&a.sa_mask);
        
        sigaction(SIGINT,&a,0);

        while(100000);


        //getchar();

        //trigger_segfault();

}
/*
========================================================================================================
Output:

./a.out
When terminating a process on terminal by using ctrl + c you will get a interrupt signal
^C
Interrupt signal wasdetected 

========================================================================================================
*/
