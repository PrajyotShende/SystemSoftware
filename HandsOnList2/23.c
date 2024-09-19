/*
========================================================================================================
Name : 23
Author : Prajyot Shende
Description : Write a program to print the maximum number of files that can be opened within a process and size of a pipe (circular buffer).
Date: 12 Sept, 2024.
========================================================================================================
*/

#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<limits.h>
#include<stdio.h>

int main() 
{
	long Max_open; 
	long P_size;

	mkfifo("FIFO_23", S_IRWXU);

	Max_open = sysconf(_SC_OPEN_MAX);
	
	printf("Maximum no of files that can be open in a process : %ld\n", Max_open);

	printf("Maximum Size of Pipe: %d\n", PIPE_BUF);

	return 0;
}

/*
========================================================================================================
Output:

./a.out
Maximum no of files that can be open in a process : 1024
Maximum Size of Pipe: 4096


========================================================================================================
*/
