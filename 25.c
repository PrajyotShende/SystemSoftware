/*
========================================================================================================

Name: 25
Author: Prajyot Shende
Description: Write a program to create three child processes. The parent should wait for a particular child (use waitpid system call).
Date: 29th August, 2024

========================================================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
	int a = fork();

	if(!a)
	{
		sleep(3);
		printf("1st child\n");
	}
	else
	{
		int b = fork();
		if(!b)
		{
			sleep(5);
			printf("2nd child\n");
		}
		else
		{
			int c = fork();
			if(!c)
			{
				sleep(4);
				printf("3rd child\n");
			}
			else
			{
				printf("Child 2 waiting for we are\n");
				waitpid( b, NULL, 0 );
			}
		}
	}
}


/*
========================================================================================================
Output:

./a.out
Child 2 waiting for we are
1st child
3rd child
2nd child


========================================================================================================
*/
