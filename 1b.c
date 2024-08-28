#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
int main()
{
	int z = link("hard.txt","hardlnk");
	if(z==0)
	printf("hard-link created successfully done");
	else 
	printf("some error occured man");
	return 0;
}
