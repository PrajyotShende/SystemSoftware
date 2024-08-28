#include<iostream>
#include<fcntl.h>
using namespace std;
int main()
{
	int a = creat("FD",0777);
		if(a==-1) 
			cout<<"error while creation, please try again";
		else 
			cout<<"file creation completed";
	cout<<a;
}
