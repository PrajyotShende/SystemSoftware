#include<stdio.h>
#include<unistd.h>
#include<sys/resource.h>
int main()
{
	int a = fork();
	if(a==0)
	{
		printf("Process ID of PArent is %d\n", getppid());
		printf("Process ID of Child  is %d\n", getpid());
	}
		return 0;	
}
