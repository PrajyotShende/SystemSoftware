/*
========================================================================================================
Name : 12
Author : Prajyot Shende
Description : Write a program to create an orphan process. Use kill system call to send SIGKILL signal to the parent process from the child process.
Date: 12 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

int main() 
{
	int a = fork();
	
	if (a < 0) 
	{
		perror("Error in creating child process");
		exit(1);
	} 
	else if (a == 0) 
	{
		printf("Child Process ID is %d\n", getpid());
		printf("Parents's process ID to be killed is %d\n", getppid());
		
		kill(getppid(), SIGKILL);
		
		printf("Child is now an orphan.\n");
		sleep(5);
		printf("Child %d now has a different different Parent ID: %d\n", getpid(), getppid());
		exit(0);
	}
       	else 
	{
		printf("Parent process id :-%d\n", getpid());
		printf("Child process id :-%d\n", a);
		sleep(10);
	}
}


/*
========================================================================================================
Output:

./a.out
a.out
Parent process id :-11171
Child process id :-11172
Child Process ID is 11172
Parents's process ID to be killed is 11171
Child is now an orphan.
Killed
Child 11172 now has a different different Parent ID: 1940


========================================================================================================
*/
