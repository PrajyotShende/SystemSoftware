/*
=========================================================================================================
Name: 18a
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
		int t2;
	};

	struct buyticket x = {1,0};
	struct buyticket y = {2,0};
	struct buyticket z = {3,0};

	struct buyticket buff[3];

	buff[0] = x;
	buff[1] = y;
	buff[2] = z;

	int a = open("18.txt",O_CREAT|O_RDWR,0644);
	
	int b = write(a,&buff,sizeof(buff));

	cout<<"Three tickets windows in existance";

	//char p[100];

	//read(a,&p,sizeof(a));
	
	//for(int i=0;i<99;i++)
	//cout<<p[i];

	close(a);

	return 0;

}


/*
================================================
Output: 

./a.out 
Three tickets windows in existance 


=======================================================
*/
