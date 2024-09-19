/*
========================================================================================================
Name : 2
Author : Prajyot Shende
Description : Write a program to print the system resource limits. Use getrlimit system call.
Date: 12 Sept, 2024.
========================================================================================================
*/

#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>

struct R {
	const char *z;
	int a;
};

void print(int a, const char *z){
	struct rlimit l;
	if(getrlimit(a, &l) == 0)
	{
		printf("%s :\n", z);
		if(l.rlim_cur == RLIM_INFINITY)
			printf("Soft Limit: No Limit for this resource\n");
		else
			printf("Soft Limit: %lu\n", l.rlim_cur); 

		if(l.rlim_max == RLIM_INFINITY)
			printf("Hard Limit: No Limit for this resource\n");
		else
                        printf("Hard Limit: %lu\n", l.rlim_max);
	}
	else
	{
		perror("Cannot get the limits of the requested resources");
	}
	printf("\n");
}

int main()
{
	struct R input[] =
	{
		{ "Time Limit of CPU",RLIMIT_CPU },
	       	{ "Limit of File SIZE",RLIMIT_FSIZE },
		{ "Limits of Data Seg",RLIMIT_DATA },
	       	{ "Stack Size limit is ",RLIMIT_STACK, },
	       	{ "Core files size limit is", RLIMIT_CORE },
	       	{ "Resident set size",RLIMIT_RSS },
		{ "Max No. of corresponding Processes",RLIMIT_NPROC  },
	       	{ "Max No. of Open files",RLIMIT_NOFILE },
		{ "Unaccessible or Locked memory limit is",RLIMIT_MEMLOCK },
	       	{ "Max Address space",RLIMIT_AS }
	};

	int size = sizeof(input) / sizeof(input[0]);
	for(int i = 0; i < size; i++)
	{
		print(input[i].a, input[i].z);
	}
}


/*
========================================================================================================
Output:

./a.out
Time Limit of CPU :
Soft Limit: No Limit for this resource
Hard Limit: No Limit for this resource

Limit of File SIZE :
Soft Limit: No Limit for this resource
Hard Limit: No Limit for this resource

Limits of Data Seg :
Soft Limit: No Limit for this resource
Hard Limit: No Limit for this resource

Stack Size limit is  :
Soft Limit: 8388608
Hard Limit: No Limit for this resource

Core files size limit is :
Soft Limit: 0
Hard Limit: No Limit for this resource

Resident set size :
Soft Limit: No Limit for this resource
Hard Limit: No Limit for this resource

Max No. of corresponding Processes :
Soft Limit: 62515
Hard Limit: 62515

Max No. of Open files :
Soft Limit: 1024
Hard Limit: 1048576

Unaccessible or Locked memory limit is :
Soft Limit: 2058096640
Hard Limit: 2058096640

Max Address space :
Soft Limit: No Limit for this resource
Hard Limit: No Limit for this resource

========================================================================================================
*/
