#include <iostream>
#include <fcntl.h>
#include <unistd.h>
using namespace std;
int main()
{
	int t = 0;
	//int readnum;
	int a = open("17a.txt",O_CREAT|O_RDWR,0644);
	
	int l = lseek(a,0,SEEK_SET);
	//cout<<l<<endl;
	
	ssize_t  b = write(a,&t,sizeof(t));
	//cout<<b<<endl;

	int l2 = lseek(a, 0, SEEK_SET);
	//cout<<l2<<endl;

	//ssize_t c = read(a,&readnum,sizeof(readnum));
	//cout<<c<<endl;

	//cout<<readnum<<endl;

	close(a);

	return 0;
}
