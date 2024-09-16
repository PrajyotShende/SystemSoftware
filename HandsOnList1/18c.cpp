/*
=========================================================================================================
Name: 18c
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
        cout<<"Enter the window no. you would like to see the tickets "<<endl;
        int t;
        cin>>t;
        int l = lseek(a,(t-1)*sizeof(struct buyticket),SEEK_SET);
        //cout<<"lssek"<<l<<endl;

        struct flock READLOCK;
        READLOCK.l_type = F_RDLCK;
        READLOCK.l_whence = SEEK_CUR;
        READLOCK.l_start = 0;
        READLOCK.l_len = sizeof(struct buyticket);

        int d = fcntl(a,F_SETLKW,&READLOCK);

        int r1 = read(a,&p,sizeof(struct buyticket));
        //cout<<r1<<endl;

        cout<<"Ticket sold at window "<< p.w <<" is "<<p.t1<<endl;

        cout<<"To end press Enter";

        getchar();

        getchar();

        //p.t1++;

        //cout<<"Your window no. " <<p.w<< ". Your ticket no "<<p.t1<<endl;

        int l1 = lseek(a,(t-1)*sizeof(struct buyticket),SEEK_SET);
        //cout<<l1<<endl;

        //int r2 = write(a,&p,sizeof(struct buyticket));

        int d1 = fcntl(a,F_UNLCK,&READLOCK);

        close(a);

        return 0;


}
         
/*
=======================================================
Output:

./a.out
Enter the window no. you would like to see the tickets 
2
Ticket sold at window 2 is 6
To end press Enter
	

=======================================================
*/
