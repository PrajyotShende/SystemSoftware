/*
========================================================================================================

Name: 6
Author: Prajyot Shende
Description: Write a program to take input from STDIN and display on STDOUT. Use only read/write system calls
Date: 29th August, 2024

========================================================================================================
*/

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
using namespace std;
int main()
{	
	cout<<"Write something less than 20 bits."<<endl;
	char a[20];
	int s = read(0,a,20);
	if(s==-1) cout<< "errorrrrrrrrrrrr"<<endl;
	else cout<<s<<" bites read properly so chill"<<endl;

        s = write(1,a,s);
	if(s==-1) cout<<"but some error in writing bro, so work harder"<<endl;
}



/*
========================================================================================================
Output:

./a.out
Write something less than 20 bits.
dasdasdw
9 bites read properly so chill
dasdasdw

========================================================================================================
*/
