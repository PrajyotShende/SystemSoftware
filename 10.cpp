/*
========================================================================================================

Name: 10
Author: Prajyot Shende
Description: Write a program to open a file with read write mode, write 10 bytes, move the file pointer by 10 bytes (use lseek) and write again 10 bytes.
	a. check the return value of lseek
	b. open the file with od and check the empty spaces in between the data.
Date: 29th August, 2024

========================================================================================================
*/


#include <fcntl.h>
#include <bits/stdc++.h>
#include <iostream>
using namespace std;
int main()
{
	int a = open("10.txt",O_CREAT|O_RDWR,0644);
	if(a==-1)
	{       
		cout<<"File was not been created, please try again later\n";
		return 0;
	}
	//cout<<a;
	char x[100] = "gv ym nb   \n";
	int b = write(a,x,10);
	//cout<<b;
	int c = lseek(a,10,SEEK_CUR);
	cout<<"lseek = "<<c<<endl;
	char y[100] = "Prajyot Shende";
	int d = write(a,y,10);

	cout<<"Eerything worked perfectly, now you can check the file 10.txt and to see the black spaces use od -c 10.txt\n";
	//cout<<d;	

}

/*
========================================================================================================
Output:

./a.out
lseek = 20
Eerything worked perfectly, now you can check the file 10.txt and to see the black spaces use od -c 10.txt

od -c 10.txt
0000000   g   v       y   m       n   b          \0  \0  \0  \0  \0  \0
0000020  \0  \0  \0  \0   P   r   a   j   y   o   t       S   h
0000036


==========================================================================================================
*/
