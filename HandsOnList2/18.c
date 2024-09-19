/*
========================================================================================================
Name : 18
Author : Prajyot Shende
Description : Write a program to find out total number of directories on the pwd. Execute ls -l | grep ^d | wc. Use only dup2.
Date: 12 Sept, 2024.
========================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() 
{
	int arr1[2], arr2[2];
	int a, b, c;
	
	if (pipe(arr1) == -1 || pipe(arr2) == -1) 
	{
		printf("Failed to establish connection");
		exit(1);
	}
	
	a = fork();
	if (a == -1) 
	{
		printf("Unable to create a child process");
		exit(1);
	}

	if (a == 0) 
	{
		dup2(arr1[1], 1);
		close(arr1[0]);
		close(arr1[1]);
		close(arr2[0]);
		close(arr2[1]);
		execlp("ls", "ls", "-l", NULL);
		exit(1);
	}

	b = fork();
	if (b == -1) 
	{
		printf("Unable to create a child process");
		exit(1);
	}

	if (b == 0) 
	{
		dup2(arr1[0], 0);
		dup2(arr2[1], 1);
		close(arr1[0]);
		close(arr1[1]);
		close(arr2[0]);
		close(arr2[1]);
		execlp("grep", "grep", "^d", NULL);
		exit(1);
	}

	close(arr1[0]);
	close(arr1[1]);

	c = fork();
	if (c == -1) 
	{
		printf("Unable to create a child process");
		exit(1);
	}

	if (c == 0) 
	{
		dup2(arr2[0], 0);
		close(arr2[1]);
		close(arr2[0]);
		execlp("wc", "wc", "-l", NULL);
		exit(1);
	}

	close(arr2[0]);
	close(arr2[1]);

	int i=0;
	while(i<3)
	{
		wait(NULL);
		i++;
	}

	return 0;
}

/*
========================================================================================================
Output:

./a.out
0

========================================================================================================
*/
