#include <iostream>
#include <cstdlib>
#include <fcntl.h>
using namespace std;
int main()
{
	int a = open("FD.txt",O_CREAT|O_EXCL,O_RDWR);
	if(a==-1)
		cout<<"File not created";
	else
		cout<<"File created";
} 


