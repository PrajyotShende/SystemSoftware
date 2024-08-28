#include <fcntl.h>
#include <bits/stdc++.h>
#include <iostream>
using namespace std;
int main()
{
	int a = open("10.txt",O_CREAT|O_RDWR,0777);
	if(a==-1)
	{       
		cout<<"File was not been created, please try again later";
		return 0;
	}
	//cout<<a;
	char x[100] = "gv ym nb   \n";
	int b = write(a,x,10);
	//cout<<b;
	int c = lseek(a,10,SEEK_CUR);
	cout<<"lseek = "<<c<<endl;
	char y[100] = "Prajyot Shende";
	int d = write(a,y,10);

	cout<<"Eerything worked perfectly, now you can check the file 10.txt and to see the black spaces use od -c 10.txt";
	//cout<<d;	

}
