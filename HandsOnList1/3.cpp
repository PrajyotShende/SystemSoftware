/*
========================================================================================================

Name: 3
Author: Prajyot Shende
Description: Write a program to create a file and print the file descriptor value. Use creat ( ) system call
Date: 29th August, 2024

========================================================================================================
*/

#include<iostream>
#include<fcntl.h>
using namespace std;
int main()
{
	int a = creat("FD",0644);
		if(a==-1) 
			cout<<"error while creation, please try again";
		else 
			{
				cout<<"file creation completed\n";
				cout<<a<<" is the File Descriptor of the created file\n";
			}
}

/*
========================================================================================================
Output:

./a.out
file creation completed
3 is the File Descriptor of the created file


========================================================================================================
*/
