/*
========================================================================================================

Name: 24
Author: Prajyot Shende
Description: Write a program to create an orphan process.
Date: 29th August, 2024

========================================================================================================
*/

#include<stdio.h>
#include<unistd.h>
int main()
{
	int a = fork();
	if(!a)
	{
		printf("Child is not an orphan, its parent process is ID is %d\n",getppid());
		sleep(10);
		printf("Child after orphan its pid is %d\n",getppid());
	}
	else sleep(1);
	return 0;
}

/*
========================================================================================================
Output:

./a.out
Child is not an orphan, its parent process is ID is 11629
prajyot-shende@prajyot-shende-Predator-PHN16-71:~/Downloads/SystemSoftware$ Child after orphan its pid is 1920


========================================================================================================
*/
