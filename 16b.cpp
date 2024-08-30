/*
========================================================================================================

Name: 16b
Author: Prajyot Shende
Description: Write a program to perform mandatory locking.
        a. Implement write lock
        b. Implement read lock
Date: 29th August, 2024

========================================================================================================
*/

#include<sys/file.h>
#include<iostream>
#include<fcntl.h>
#include<unistd.h>
using namespace std;
int main()
{
        cout<<"Trying To Acquire Read Lock PLEASE STAND BY......\n";
        
	struct flock READLOCK;
        
	READLOCK.l_type = F_RDLCK;
	READLOCK.l_whence = SEEK_CUR;
        READLOCK.l_start = 0;
        READLOCK.l_len = 0;
        
	int a = open("16a.txt",O_RDONLY);
        
	int b = fcntl(a,F_SETLKW,&READLOCK);
        
	cout<<"Acquired READD Lock. Press Enter to Exit.\n";
        
	getchar();
        
	int c = fcntl(a,F_UNLCK,&READLOCK);
        
	cout<<"RD Lock Unlocked\n";
        
	close(a);
}

/*
========================================================================================================
Output:

terminal 1:
./a.out
Trying To Acquire Read Lock PLEASE STAND BY......
Acquired READD Lock. Press Enter to Exit.

terminal 2:
./a.out
Trying To Acquire Read Lock PLEASE STAND BY......
Acquired READD Lock. Press Enter to Exit.

terminal 3:
./a.out
Trying To Acquire Write Lock. Please stand by......

========================================================================================================
*/


