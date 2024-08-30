#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
	int a = fork();

	if(!a)
	{
		sleep(3);
		printf("1st child\n");
	}
	else
	{
		int b = fork();
		if(!b)
		{
			sleep(5);
			printf("2nd child\n");
		}
		else
		{
			int c = fork();
			if(!c)
			{
				sleep(8);
				printf("3rd child\n");
			}
			else
			{
				printf("Child 2 waiting for we are\n");
				waitpid( b, NULL, 0 );
			}
		}
	}
}
