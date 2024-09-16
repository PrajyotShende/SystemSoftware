#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
void o()
{
        printf("Your Time IS OVER\n");
        exit(0);
}


void main()
{
	//struct timeval t1;
	//t1.tv_sec = 10;
        //t1.tv_usec = 10;

	struct itimerval t;
	t.it_value.tv_sec = 10;
	t.it_value.tv_usec = 10;
        t.it_interval.tv_sec = 10;
	t.it_interval.tv_usec = 10;

	/*
	struct itimerval t;
        t.it_value = t1;
        t.it_value = t1;
        t.it_interval = t1;
        t.it_interval = t1;
	*/
	
	signal(SIGALRM,o);

	int srttimer = setitimer(ITIMER_REAL, &t, 0);
	
	if(srttimer == -1)
	{
		perror("Not able to ste timer currently. Please try again later");
		exit(0);
	}
	
	while(10000000);


}
