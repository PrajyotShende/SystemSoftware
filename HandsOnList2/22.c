/*
========================================================================================================
Name : 22
Author : Prajyot Shende
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use select system call with FIFO.
Date: 12 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/select.h>
#include<sys/stat.h>
#include<sys/types.h>

int main()
{
	mkfifo("FIFO_22",0666);
	int a = open("FIFO_22", O_RDONLY | O_NONBLOCK);
	if(a==-1)
	{
		perror("open");
		exit(1);
	}

	fd_set b;;
	FD_ZERO(&b);
	FD_SET(a, &b);

	struct timeval time = {10, 0};

	int p = select(a + 1, &b, NULL, NULL, &time);

	if(p == -1)
	{
		perror("Select");
		close(a);
		exit(1);
	}
	if (p == 0) printf("TIME UP\n");
	else if(FD_ISSET(a, &b))
	{
		char z[100];
		int n = read(a, &z, sizeof(z));
		if(n > 0)
			printf("Data from FIFO: %s\n", z);
		else
			printf("No data");
	}
}

/*
========================================================================================================
Output:

./a.out
HI
TIME UP
prajyot-shende@prajyot-shende-Predator-PHN16-71:~/Documents/SystemSoftware/HandsOnList2$ HI
HI: command not found

./a.out
TIME UP

========================================================================================================
*/
