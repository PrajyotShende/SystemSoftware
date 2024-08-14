#include <bits/stdc++.h>
#include <iostream>
#include <cstdlib>
#include <fcntl.h>
using namespace std;
int main(){
 	int a7 = open("7a.txt",O_RDWR,0777);
	int b7 = open("7b.txt",O_RDWR,0777);
//cout<<a7<<endl;
//cout<<b7<<endl;
 char x[10]="file12345";
 char y[10]="file23456";
 char z[10];
//cout<<"hogaya read"<<endl;
//cout<<"yeh bhi read hogaya bhai";
int p = write(a7,x,10);
cout<<p<<endl;
int q = write(b7,y,10);
cout<<q<<endl;
int r = lseek(a7,0,SEEK_SET);
cout<<r<<endl;
int s = read(a7,z,10);
cout<<s<<endl;
int t = write(b7,z,10);
cout<<t<<endl;
//int u = write(1,b7,20);
close(a7);
close(b7);


}
