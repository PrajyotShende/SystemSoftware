#include<iostream>
#include<fcntl.h>
using namespace std;
int main()	
{

        int a = open("1st.txt",O_CREAT,0755);
	int b = open("2nd.txt",O_CREAT,0755);
	int c = open("3rd.txt",O_CREAT,0755);
	int d = open("4th.txt",O_CREAT,0755);
	int e = open("5th.txt",O_CREAT,0755);
	cout<<a<<b<<c<<d<<e;
	while(true);
}

