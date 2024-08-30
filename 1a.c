/*
========================================================================================================

Name: 1a
Author: Prajyot Shende
Description: Create the following types of a files using (i) shell command (ii) system call
		a. soft link (symlink system call)
		b. hard link (link system call)
		c. FIFO (mkfifo Library Function or mknod system call)
Date: 29th August, 2024

========================================================================================================
*/

#include<stdio.h>
#include<unistd.h>
int main(){
	int slink = symlink("filenew","sftlnk");
	if(slink == 0){
		printf("softlink created successfully");
	}
	else
	{
		printf("Softlink cannot be created please try again later\n");
		printf("Softlink may already be created, try removing sftlnk and try again\n");
	}
}

/*
========================================================================================================
Output:

./a.out
softlink created successfully

========================================================================================================
*/
