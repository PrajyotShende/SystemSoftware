#include <bits/stdc++.h>
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
