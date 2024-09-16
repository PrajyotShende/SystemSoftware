/*
========================================================================================================

Name: 4
Author: Prajyot Shende
Description: Write a program to open an existing file with read write mode. Try O_EXCL flag also.
Date: 29th August, 2024

========================================================================================================
*/

#include <iostream>
#include <cstdlib>
#include <fcntl.h>
using namespace std;
int main()
{
	int a = open("FD.txt",O_CREAT,O_RDWR);
	//cout<<a<<endl;
	if(a==-1)
	{
		cout<<" file already exists, please try again later\n";	
		return 0;	
	}
	else
		cout<<"File careation completed\n";



	int b = open( "FD.txt", O_CREAT | O_EXCL, O_RDWR );
        if(b==-1)
                cout<<"File not opened, so O_EXCL worked properly";
	else
                cout<<"some error";
 
} 

/*
========================================================================================================
Output:

./a.out
File careation completed
File not opened, so O_EXCL worked properly

========================================================================================================
*/
