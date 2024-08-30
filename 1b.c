/*
========================================================================================================

Name: 1b
Author: Prajyot Shende
Description: Create the following types of a files using (i) shell command (ii) system call
                a. soft link (symlink system call)
                b. hard link (link system call)
                c. FIFO (mkfifo Library Function or mknod system call)
Date: 29th August, 2024

========================================================================================================
*/

#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
int main()
{
	int z = link("hard.txt","hardlnk");
	if(z==0)
	printf("hard-link created successfully done");
	else {
		printf("Hardlink cannot be created please try again later\n");
		printf("Hardlink may already be created, try removing hardlnk and try again");
	}
		return 0;
}

/*
========================================================================================================
Output:

 ./a.out
hard-link created successfully done

========================================================================================================
*/
