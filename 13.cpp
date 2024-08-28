#include <iostream>
#include <unistd.h>
#include <fcntl.h>
using namespace std;
int main()
{
	int a;
	struct timeval t;
	fd_set z;
	FD_ZERO(&z);
	FD_SET(0,&z);

	t.tv_sec = 10;

	a = select(1,&z,NULL,NULL,&t);

	if(a==-1) cout<<"ERROR ERROR ERROR....";
	else if (a==0) cout<<"NO INPUT found";
	else cout<<"Got something";
}
