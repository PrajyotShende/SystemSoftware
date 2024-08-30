/*
========================================================================================================

Name: 13
Author: Prajyot Shende
Description: Write a program to wait for a STDIN for 10 seconds using select. Write a proper print statement to verify whether the data is available within 10 seconds or not (check in $man 2 select).
Date: 29th August, 2024

========================================================================================================
*/

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
using namespace std;
int main()
{
	int a;
	struct timeval t;
	fd_set z;
	FD_ZERO(&z);
	FD_SET(0,&z);

	t.tv_sec = 10;

	a = select(1,&z,NULL,NULL,&t);

	if(a==-1) cout<<"ERROR ERROR ERROR....\n";
	else if (a==0) cout<<"NO INPUT found\n";
	else cout<<"Got something\n";
}


/*
========================================================================================================
Output:

./a.out
saddw
Got something

./a.out
NO INPUT found

========================================================================================================
*/
