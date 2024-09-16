/*
=========================================================================================================
Name: 18b
Author: Prajyot Shende
Description: Write a program to perform Record locking.
		a. Implement write lock
		b. Implement read lock
Create three records in a file. Whenever you access a particular record, first lock it then modify/access
to avoid race condition.
Date: 28 Aug 2024
==========================================================================================================
*/

#include<sys/file.h>
#include<iostream>
#include<fcntl.h>
#include<unistd.h>
using namespace std;
int main()
{
        struct buyticket{
                int w;
                int t1;
        };
	
	struct buyticket p;
	int a = open("18.txt",O_RDWR,0644);
	cout<<"Enter the window no. you would like to book ticket from 1/2/3 "<<endl;
	int t;
	cin>>t;
	int l = lseek(a,(t-1)*sizeof(struct buyticket),SEEK_SET);
	//cout<<"lssek"<<l<<endl;

	struct flock WRITELOCK;
        WRITELOCK.l_type = F_WRLCK;
        WRITELOCK.l_whence = SEEK_CUR;
        WRITELOCK.l_start = 0;
        WRITELOCK.l_len = sizeof(struct buyticket);

        int d = fcntl(a,F_SETLKW,&WRITELOCK);

	int r1 = read(a,&p,sizeof(struct buyticket));
	//cout<<r1<<endl;

	cout<<"Ticket sold at window "<< p.w <<" is "<<p.t1<<endl;

	cout<<"To buy a ticket press enter";

	getchar();

	getchar();

	p.t1++;

	cout<<"Your window no. " <<p.w<< ". Your ticket no "<<p.t1<<endl;

	int l1 = lseek(a,(t-1)*sizeof(struct buyticket),SEEK_SET);
	//cout<<l1<<endl;

	int r2 = write(a,&p,sizeof(struct buyticket));

	int d1 = fcntl(a,F_UNLCK,&WRITELOCK);
	
	close(a);

	return 0;


}




/*
================================================
Output: 
	terminal 1
	./a.out 
	Enter the window no. you would like to book ticket from 1/2/3
	2
	Ticket sold at window 2 is 0
	To buy a ticket press enter
	Your window no. 2. Your ticket no 1

	terminal 2
	./a.out ticket.txt
	Enter the window no. you would like to book ticket from 1/2/3
	2

	terminal 3
	./a.out ticket.txt
	Enter the window no. you would like to book ticket from 1/2/3
	1
	Ticket sold at window 1 is 2
	To buy a ticket press enter
	Your window no. 1. Your ticket no 2

================================================
*/
