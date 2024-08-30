/*
========================================================================================================

Name: 21
Author: Prajyot Shende 
Description: Write a program, call fork and print the parent and child process id.
Date: 29th August, 2024

========================================================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/resource.h>
int main()
{
	int a = fork();
	if(a==0)
	{
		printf("Process ID of PArent is %d\n", getppid());
		printf("Process ID of Child  is %d\n", getpid());
	}
		return 0;	
}

/*========================================================================================================
Output:

./a.out
Process ID of PArent is 11419
Process ID of Child  is 11420

========================================================================================================
*/
