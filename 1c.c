/*
========================================================================================================

Name: 1c
Author: Prajyot Shende
Description: Create the following types of a files using (i) shell command (ii) system call
                a. soft link (symlink system call)
                b. hard link (link system call)
                c. FIFO (mkfifo Library Function or mknod system call)
Date: 29th August, 2024

========================================================================================================
*/

#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
int main(){
	int a = mknod("fifo",0644,0);
	if(a==0){
		printf("successfully created\n");
	}
	else
		printf("error\n");
}

/*
========================================================================================================
Output:

./a.out
successfully created

========================================================================================================
*/
