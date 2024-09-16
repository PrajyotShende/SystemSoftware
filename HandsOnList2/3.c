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
