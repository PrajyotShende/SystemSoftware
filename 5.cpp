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
	cout<<"It will run in an infinte loop after you press something, parallely check /proc directory by using :- ps -e|grep a.out for process id and for printing the table use command :- ls -la/proc/process_id/fd\n";
	getchar();
	//cout<<a<<b<<c<<d<<e;
	while(true);
}

