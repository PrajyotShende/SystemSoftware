/*
========================================================================================================

Name: 5
Author: Prajyot Shende
Description: Write a program to create five new files with infinite loop. Execute the program in the background and check the file descriptor table at /proc/pid/fd.
Date: 29th August, 2024

========================================================================================================
*/

#include<iostream>
#include<fcntl.h>
using namespace std;
int main()	
{

        int a = open("1st.txt",O_CREAT,0644);
	int b = open("2nd.txt",O_CREAT,0644);
	int c = open("3rd.txt",O_CREAT,0644);
	int d = open("4th.txt",O_CREAT,0644);
	int e = open("5th.txt",O_CREAT,0644);
        cout<<"It will run in an infinte loop after you press something, parallely check /proc directory by using  ps -e|grep a.out for process id and for printing the table use command :- ls -la/proc/process_id/fd\n";
	
	
	cout<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<" "<<"are the file descriptors of the opened files";
	getchar();
	while(true);
}


/*
========================================================================================================
Output:- 

./a.out
It will run in an infinte loop after you press something, parallely check /proc directory by using  ps -e|grep a.out for process id and for printing the table use command :- ls -la/proc/process_id/fd
3 4 5 6 7 are the file descriptors of the opened files


ls -la /proc/9795/fd
total 0
dr-x------ 2 prajyot-shende prajyot-shende  8 Aug 30 15:30 .
dr-xr-xr-x 9 prajyot-shende prajyot-shende  0 Aug 30 15:30 ..
lrwx------ 1 prajyot-shende prajyot-shende 64 Aug 30 15:30 0 -> /dev/pts/0
lrwx------ 1 prajyot-shende prajyot-shende 64 Aug 30 15:30 1 -> /dev/pts/0
lrwx------ 1 prajyot-shende prajyot-shende 64 Aug 30 15:30 2 -> /dev/pts/0
lr-x------ 1 prajyot-shende prajyot-shende 64 Aug 30 15:30 3 -> /home/prajyot-shende/Downloads/SystemSoftware/1st.txt
lr-x------ 1 prajyot-shende prajyot-shende 64 Aug 30 15:30 4 -> /home/prajyot-shende/Downloads/SystemSoftware/2nd.txt
lr-x------ 1 prajyot-shende prajyot-shende 64 Aug 30 15:30 5 -> /home/prajyot-shende/Downloads/SystemSoftware/3rd.txt
lr-x------ 1 prajyot-shende prajyot-shende 64 Aug 30 15:30 6 -> /home/prajyot-shende/Downloads/SystemSoftware/4th.txt
lr-x------ 1 prajyot-shende prajyot-shende 64 Aug 30 15:30 7 -> /home/prajyot-shende/Downloads/SystemSoftware/5th.txt


========================================================================================================
*/
