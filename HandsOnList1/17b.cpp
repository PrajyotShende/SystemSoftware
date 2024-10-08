/*
============================================================================================
Name: 17b
Author: Prajyot Shende
Description:  Write a program to simulate online ticket reservation. Implement write lock
Write a program to open a file, store a ticket number and exit. Write a separate program, to
open the file, implement write lock, read the ticket number, increment the number and print
the new ticket number then close the file.
Date: 28 Aug 2024
============================================================================================
*/

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
using namespace std;
int main()
{
        int t1;

	int a = open("17a.txt",O_RDWR,0644);
        	
	cout<<"Trying To Acquire Write Lock. Please stand by......\n";

        struct flock WRITELOCK;
        WRITELOCK.l_type = F_WRLCK;
        WRITELOCK.l_whence = SEEK_SET;
        WRITELOCK.l_start = 0;
        WRITELOCK.l_len = 0;

        int d = fcntl(a,F_SETLKW,&WRITELOCK);

        cout<<"Acquired Write Lock.\n";
	
	int c = lseek(a,0,SEEK_SET);
	//cout<<c<<endl;
        
	ssize_t  b = read(a,&t1,sizeof(t1));
	
	cout<<"Number of tickets sold = "<<t1<<endl;

	cout<<"To buy a ticket, press enter";

	getchar();

	t1++;

	cout<<"Your Ticket no is "<<t1<<endl;

	int l = lseek(a,0,SEEK_SET);
	//cout<<"lseek - "<<l<<endl;

	int w = write(a,&t1,sizeof(a));
	//cout<<"write"<<w<<endl;

	int u = fcntl(a,F_UNLCK,&WRITELOCK);
	//cout<<"Unlocked"<<u<<endl;

	//cout<<b<<endl;
	//cout<<t1<<endl;

	close(a);
	return 0;
}


/*
================================================
Output: 

terminal 1
./a.out
Trying To Acquire Write Lock. Please stand by......
Acquired Write Lock.
Number of tickets sold = 0
To buy a ticket, press enter
Your Ticket no is 1


terminal 2
Trying To Acquire Write Lock. Please stand by......


================================================
*/
