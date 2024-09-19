/*
========================================================================================================
Name : 8.e
Author : Prajyot Shende
Description : Write a separate program using signal system call to catch the signal SIGALRM (use setitimer system call).
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
        printf("Alarm Signal Detected\n");
        exit(1);
}


int main()
{
	
        signal(SIGALRM, sig);
        struct itimerval t;
        t.it_value.tv_sec = 1;
        t.it_value.tv_usec = 10;
        t.it_interval.tv_sec = 10;
        t.it_interval.tv_usec = 0;
	int srttimer = setitimer(ITIMER_REAL, &t, 0);

        if(srttimer == -1)
        {
                perror("Not able to ste timer currently. Please try again later");
                exit(0);
        }


        while(10000);

}

/*
========================================================================================================
Output:

./a.out
Alarm Signal Detected


========================================================================================================
*/
