/*
========================================================================================================

Name: 26b
Author: Prajyot Shende
Description: Write a program to execute an executable program.
	a. use some executable program
	b. pass some input to an executable program. (for example execute an executable of $./a.out name)
Date: 29th August, 2024

========================================================================================================
*/

#include<stdio.h>
#include<unistd.h>

int main( int argc, char** argv ){
	if( argc < 2 ){
		printf("Please enter the file name corrctly\n" );
		return 0;
	}

	execl( "/home/prajyot-shende/Downloads/SystemSoftware/b.out", "b.out", argv[1], NULL );
	
	return 0;
}


/*
========================================================================================================
Output:

g++ 9.cpp -o b.out

./a.out 10.txt
I-node = 2381989
#hardlinks = 33204
uid = 1
gid = 1000
size = 1000
block-size = 4096
#blocks = 8
last_access = Thu Aug 29 19:23:19 2024

last_modified = Wed Aug 28 19:19:28 2024

last_changed = Wed Aug 28 19:19:28 2024


========================================================================================================
*/
