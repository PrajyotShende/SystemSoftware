#include<stdio.h>
#include<unistd.h>
int main()
{
	int a = fork();
	if(!a)
	{
		printf("Child is not an orphan, its parent process is ID is %d\n",getppid());
		sleep(10);
		printf("Child after orphan %d\n",getppid());
	}
	else sleep(1);
	return 0;
}
