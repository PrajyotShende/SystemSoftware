/*
========================================================================================================
Name : 13
Author : Prajyot Shende
Description : Write two programs: first program is waiting to catch SIGSTOP signal, the second program will send the signal (using kill system call). Find out whether the first program is able to catch the signal or not.
Date: 12 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<signal.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
	int a;
	printf("Enter A process no : ");
	scanf("%d", &a);
	int b =  kill(a, SIGSTOP); 

	if(b==-1)
		perror("Cannot send kill signal");
}


/*
========================================================================================================
Output:

./a.out
Enter A process no : 11249


========================================================================================================
*/
