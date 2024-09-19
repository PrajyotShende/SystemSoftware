/*
========================================================================================================
Name : 8.f
Author : Prajyot Shende
Description : Write a separate program using signal system call to catch the signal SIGVTALRM (use setitimer system call).
Date: 12 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/time.h>

void sig()
{
        printf("\n");
        printf("Virtual Signal Detected\n");
        exit(1);
}


int main()
{

        signal(SIGVTALRM, sig);
        
	struct itimerval t;
        
	t.it_value.tv_sec = 1;
        t.it_value.tv_usec = 0;
        t.it_interval.tv_sec = 0;
        t.it_interval.tv_usec = 0;
        
	int srttimer = setitimer(ITIMER_VIRTUAL, &t, NULL);

        if(srttimer == -1)
        {
                perror("Not able to ste timer currently. Please try again later");
                exit(0);
        }

	//pause();
	
	while(10000);


}


/*
========================================================================================================
Output:

./a.out
Virtual Signal Detected


========================================================================================================
*/
