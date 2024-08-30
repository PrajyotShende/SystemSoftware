/*
========================================================================================================

Name: 30
Author: Prajyot Shende
Description: Write a program to run a script at a specific time using a Daemon process.
Date: 29th August, 2024

========================================================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
int main(int argc,char** argv)
{
	if(argc<4)
	{
		printf("Please enter time in Hour Minute and Seconds Format.\n");
		return 0;
	}
	time_t a, z;
	struct tm* ending;
	
	time(&a);
	ending = localtime(&a);
	
	ending->tm_hour = atoi(argv[1]);
	ending->tm_min = atoi(argv[2]);
	ending->tm_sec = atoi(argv[3]);
	
	z = mktime(ending);
	
	int q = fork();
	
	if(q==0)
	{
		setsid();
			do{
				time(&a);
			} while (difftime(z,a)>0);

		system("echo Time Reached.\n");
	}
	else exit(0);
	return 0;
}


/*
========================================================================================================
Output:

 ./a.out 16 37 00
 Time Reached.

========================================================================================================
*/
