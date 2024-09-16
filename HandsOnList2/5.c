#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
         unsigned long a;
	 a = sysconf(_SC_ARG_MAX);
    	 printf("Max len of arg is %lu\n", a);
	 a = sysconf(_SC_CHILD_MAX);
    	 printf("Max no. of simultaneous process per user %lu\n", a);
	 a = sysconf(_SC_CLK_TCK);
    	 printf("No. of clk ticks per sec %lu\n", a);
	 a = sysconf(_SC_OPEN_MAX);
    	 printf("Max no. of files open is %lu\n", a);
	 a = sysconf(_SC_PAGESIZE);
    	 printf("Page size is %lu bytes\n", a);
	 a = sysconf(_SC_PHYS_PAGES);
    	 printf("Total no of pgs in the phys mem is %lu\n", a);
	 a = sysconf(_SC_AVPHYS_PAGES);
    	 printf("No. of curr avail pgs in the phys mem is %ld\n", a);
}

