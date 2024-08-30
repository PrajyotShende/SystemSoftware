/*
========================================================================================================

Name: 7
Author: Prajyot Shende
Description: Write a program to copy file1 into file2 ($cp file1 file2).
Date: 29th August, 2024

========================================================================================================
*/


#include <bits/stdc++.h>
#include <iostream>
#include <cstdlib>
#include <fcntl.h>
using namespace std;
int main(){
 	int a7 = open("7a.txt",O_RDWR,0644);
	int b7 = open("7b.txt",O_RDWR,0644);
//cout<<a7<<endl;
if(a7==-1) cout<<"File 7a.txt not found man, first create it"<<endl;
if(b7==-1) cout<<"File 7b.txt not found man, first create it"<<endl;
//cout<<b7<<endl;
 char x[10]="file123";
 char y[10]="file567";
 char z[10];
//cout<<"hogaya read"<<endl;
//cout<<"yeh bhi read hogaya bhai";
int p = write(a7,x,sizeof(x));
cout<<p<<endl;
int q = write(b7,y,sizeof(y));
cout<<q<<endl;
int r = lseek(a7,0,SEEK_SET);
cout<<r<<endl;
int s = read(a7,z,sizeof(z));
cout<<s<<endl;
int t = write(b7,z,sizeof(z));
cout<<"If you dont see -1 anywhere, evrything worked out fine, so now check the files 7a & 7b";
//cout<<t<<endl;
//int u = write(1,b7,20);


close(a7);
close(b7);



}



/*
========================================================================================================
Output:

./a.out
10
10
0
10
If you dont see -1 anywhere, evrything worked out fine, so now check the files 7a & 7b
prajyot-shende@prajyot-shende-Predator-PHN16-71:~/Downloads/SystemSoftware$ cat 7a.txt
file123
prajyot-shende@prajyot-shende-Predator-PHN16-71:~/Downloads/SystemSoftware$ cat 7b.txt
file567file123

========================================================================================================
*/
