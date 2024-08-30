#include<stdio.h>
#include<sys/resource.h>
#include<unistd.h>
int main()
{
	int priority = getpriority(PRIO_PROCESS,0);
	printf("Priority of the currentky running process is  %d\n",priority);
	priority = nice(10);
	printf("Priority of the process after using NICE cmd is  %d\n",priority);

}
