/*
========================================================================================================

Name: 22
Author: Prajyot Shende
Description: Write a program, open a file, call fork, and then write to the file by both the child as well as the parent processes. Check output of the file.
Date: 29th August, 2024

========================================================================================================
*/

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
int main()
{
	int a = open("22.txt",O_CREAT|O_RDWR,0644);
	fork();
	char x[20] = "PJDJCJ\n";
	write(a,x,sizeof(x));
	printf("Process ID used to write in the file is %d\n",getpid());
}

/*
========================================================================================================
Output:

./a.out
Process ID used to write in the file is 11483
Process ID used to write in the file is 11484

cat 22.txt
PJDJCJ
PJDJCJ

========================================================================================================
*/
