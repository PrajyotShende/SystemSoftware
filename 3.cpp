#include<iostream>
#include<fcntl.h>
using namespace std;
int main()
{
	int a = creat("FD",0644);
		if(a==-1) 
			cout<<"error";
		else 
			cout<<"created";
	cout<<a;
}
