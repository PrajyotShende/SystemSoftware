/*
========================================================================================================
Name : 3
Author : Prajyot Shende
Description : Write a program to set (any one) system resource limit. Use setrlimit system call.
Date: 12 Sept, 2024.
========================================================================================================
*/

#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>


int main()
{
	printf("\n");
        printf("Limits before changing for RLIMIT_NOFILE\n");

	struct rlimit l;
	getrlimit(RLIMIT_NOFILE, &l);
	printf("Soft Limit = %lu\n",l.rlim_cur);
	printf("Hard Limit = %lu\n",l.rlim_max);

	l.rlim_cur = 10;
	l.rlim_max = 10000;

	printf("\n");

	int o = setrlimit(RLIMIT_NOFILE,&l);
	if(o==0)
		printf("Limits for CPU changed successfully\n");
	else 
		printf("Cannot change the limit currently\n");

	printf("\n");
	printf("Limits before changing for RLIMIT_NOFILE\n");
	printf("Soft Limit = %lu\n",l.rlim_cur);
        printf("Hard Limit = %lu\n",l.rlim_max);
	printf("\n");
}


/*
========================================================================================================
Output:

a.out

Limits before changing for RLIMIT_NOFILE
Soft Limit = 1024
Hard Limit = 1048576

Limits for CPU changed successfully

Limits before changing for RLIMIT_NOFILE
Soft Limit = 10
Hard Limit = 10000


========================================================================================================
*/
