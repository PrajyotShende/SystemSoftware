/*
========================================================================================================

Name: 20
Author: Prajyot Shende
Description: Find out the priority of your running program. Modify the priority with nice command.
Date: 29th August, 2024

========================================================================================================
*/

#include<stdio.h>
#include<sys/resource.h>
#include<unistd.h>
int main()
{
	int priority = getpriority(PRIO_PROCESS,0);
	printf("Priority of the currentky running process is  %d\n",priority);
	priority = nice(10);
	printf("Priority of the process after using NICE cmd is  %d\n",priority);

}

/*========================================================================================================
Output:

./a.out
Priority of the currentky running process is  0
Priority of the process after using NICE cmd is  10


========================================================================================================
*/

