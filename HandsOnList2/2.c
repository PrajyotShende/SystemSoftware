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
