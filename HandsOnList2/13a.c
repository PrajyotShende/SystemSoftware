/*
========================================================================================================
Name : 13a
Author : Prajyot Shende
Description : Write two programs: first program is waiting to catch SIGSTOP signal, the second program will send the signal (using kill system call). Find out whether the first program is able to catch the signal or not.
Date: 12 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>

void sig()
{
	printf("SIGSTOP Signal Received");
}

int main()
{
	printf("PID: %d\n",getpid());
	signal(SIGSTOP, sig);
	sleep(100);
}

/*
========================================================================================================
Output:

./a.out

PID: 11249

[1]+  Stopped                 ./a.out


========================================================================================================
*/
