#include<sys/file.h>
#include<iostream>
#include<fcntl.h>
#include<unistd.h>
using namespace std;
int main()
{
	cout<<"Trying To Acquire Write Lock. Please stand by......\n";
	
	struct flock WRITELOCK;
        WRITELOCK.l_type = F_WRLCK;
        WRITELOCK.l_whence = SEEK_CUR;
        WRITELOCK.l_start = 0;
        WRITELOCK.l_len = 0;

	int a = open("16a.txt",O_WRONLY);

	int b = fcntl(a,F_SETLKW,&WRITELOCK);

	cout<<"Acquired Write Lock. Press Enter to Exit.\n";

	getchar();
	
	//WRITELOCK.l_type = F_UNLCK;

	int c = fcntl(a,F_UNLCK,&WRITELOCK);

	cout<<"Lock Unlocked\n";

	close(a);

}

