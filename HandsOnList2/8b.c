/*
========================================================================================================
Name : 8.b
Author : Prajyot Shende
Description : Write a separate program using signal system call to catch the signal SIGINT.
Date: 12 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<signal.h>
#include<stdlib.h>


void sig()
{
	printf("\n");
        printf("Interrupt signal was detected\n");
        exit(1);
}


int main()
{
        printf("When terminating a process on terminal by using ctrl + c you will get a interrupt signal\n");
        signal(SIGINT, sig);

	while(10000);

}

/*
========================================================================================================
Output:

./a.out
When terminating a process on terminal by using ctrl + c you will get a interrupt signal
^C
Interrupt signal was detected


========================================================================================================
*/
