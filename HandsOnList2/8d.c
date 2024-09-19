/*
========================================================================================================
Name : 8.d
Author : Prajyot Shende
Description : Write a separate program using signal system call to catch the signal SIGALRM (use alarm system call).
Date: 12 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>

void sig()
{
        printf("\n");
        printf("Alarm Signal Detected\n");
        exit(1);
}


int main()
{

        signal(SIGALRM, sig);
        alarm(1);
	getchar();

}


/*
========================================================================================================
Output:

./a.out
Alarm Signal Detected


========================================================================================================
*/
