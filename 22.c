#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
int main()
{
	int a = open("22.txt",O_CREAT|O_RDWR,0644);
	fork();
	char x[20] = "dtya 342 dj";
	write(a,x,sizeof(x));
	printf("Process ID used to write in the file is %d\n",getpid());
}
