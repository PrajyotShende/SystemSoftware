#include<stdio.h>
#include<unistd.h>

int main()
{
	int a = fork();
	if(a==0)
	{
		printf("Child process id is %d && Parent process id is %d ",getpid(),getppid());
	}
	else 
	{
		getchar();
		sleep(8);
		printf("Parent process id is %d ",getpid());
	}	
}
