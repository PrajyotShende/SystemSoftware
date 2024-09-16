/*
========================================================================================================

Name: 8
Author: Prajyot Shende
Description: Write a program to open a file in read only mode, read line by line and display each line as it is read. Close the file when end of file is reached.
Date: 29th August, 2024

========================================================================================================
*/

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
using namespace std;
int main(){
	char z[100];
        int r=0;
 	int read1 = open("read_linebyline.txt",O_RDONLY);
	if(read1==-1) 
	{
		cout<<"No such file in existance, please create it and write something in it";
		close(read1);
	}
	cout<<read1;
	while(1)
	{
		int a = read(read1,z+r,1);
		if(z[r]=='\n')
		{
			write(1,z,r);
			getchar();
			r=0;
			continue;
		}
		r++;
		if(a==0) 
		{
			cout<<"File reading Completd Succesfully, no problems occured";
			break;
		}
		if(a==-1)
		{
			cout<<"Cant read, some error";
		}

	}
close(read1);	
}



/*
========================================================================================================
Output:

cat read_linebyline.txt 
Pehela lin
Second Line
Tisri lineeeee
ichi ni san shi


./a.out
Pehela lin
Second Line
Tisri lineeeee
ichi ni san shi
File reading Completd Succesfully, no problems occured

========================================================================================================
*/
