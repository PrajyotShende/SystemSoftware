/*
============================================================================================
Name: 17a
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
	int t = 0;
	//int readnum;
	int a = open("17a.txt",O_CREAT|O_RDWR,0644);
	
	int l = lseek(a,0,SEEK_SET);
	//cout<<l<<endl;
	
	ssize_t  b = write(a,&t,sizeof(t));
	//cout<<b<<endl;

	int l2 = lseek(a, 0, SEEK_SET);
	//cout<<l2<<endl;

	//ssize_t c = read(a,&readnum,sizeof(readnum));
	//cout<<c<<endl;

	//cout<<readnum<<endl;
	cout<<"File has read the number"<<endl;

	close(a);

	return 0;
}

/*
================================================
Output: ./a.out 
	File has read the number 
	

================================================
*/
