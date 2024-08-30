/*
========================================================================================================

Name: 23
Author: Prajyot Shende
Description: Write a program to create a Zombie state of the running program.
Date: 29th August, 2024

========================================================================================================
*/

#include<stdio.h>
#include<unistd.h>

int main()
{
	int a = fork();
	if(a==0)
	{
		printf("Child process id is %d && Parent process id is %d ",getpid(),getppid());
	}
	else 
	{
		getchar();
		sleep(8);
		printf("Parent process id is %d ",getpid());
	}	
}

/*
========================================================================================================
Output:

./a.out
Child process id is 11546 && Parent process id is 11545 
Parent process id is 11545 

========================================================================================================
*/
