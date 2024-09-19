/*
========================================================================================================
Name : 5
Author : Prajyot Shende
Description : Write a program to print the system limitation of
		a. maximum length of the arguments to the exec family of functions.
		b. maximum number of simultaneous process per user id.
		c. number of clock ticks (jiffy) per second.
		d. maximum number of open files
		e. size of a page
		f. total number of pages in the physical memory
		g. number of currently available pages in the physical memory.
Date: 12 Sept, 2024.
========================================================================================================
*/

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

/*
========================================================================================================
Output:

./a.out
Max len of arg is 2097152
Max no. of simultaneous process per user 62515
No. of clk ticks per sec 100
Max no. of files open is 1024
Page size is 4096 bytes
Total no of pgs in the phys mem is 4019722
No. of curr avail pgs in the phys mem is 2533932

========================================================================================================
*/
