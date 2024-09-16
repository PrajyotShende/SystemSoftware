/*
========================================================================================================

Name: 29
Author: Prajyot Shende
Description: Write a program to get scheduling policy and modify the scheduling policy (SCHED_FIFO, SCHED_RR).
Date: 29th August, 2024

========================================================================================================
*/


#include<stdio.h>
#include<unistd.h>
#include<sched.h>

int main()
{
	int a = getpid();
	int s = sched_getscheduler(a);

	if (s==SCHED_FIFO) printf("Scheduling Policy is FIFO\n");
	else if (s==SCHED_RR) printf("Scheduling Policy is RR\n");
	else if (s==SCHED_OTHER) printf("Scheduling Policy is SCHED_OTHER\n");



	int change;
	printf("Give a input to change policy\n");
	printf("1 for Changing to FIFO\n");
	printf("2 for Changing to RR\n");
	printf("3 for Changing to OTHER\n");

	scanf("%d",&change);

	struct sched_param schedule;
	switch (change)
	{
		case 1:
			schedule.sched_priority = 99;
			int x = sched_setscheduler(a, SCHED_FIFO, &schedule);
			if(x==-1)
			{
				printf("Error in Setting Priority.\n");
				return 0;
			}
			break;
		case 2:
                        schedule.sched_priority = 99;

                        int y = sched_setscheduler(a, SCHED_RR, &schedule);
			if(y==-1)
			{
                                printf("Error in Setting Priority.\n");
                        	return 0;
                        }
                        break;
		case 3:
                        schedule.sched_priority = 99;
                        int z = sched_setscheduler(a, SCHED_OTHER, &schedule);
			if(z==-1)
			{
                                printf("Error in Setting Priority.\n");
                                return 0;
                        }
                        break;
		default:
			break;
	}

	int changed = getpid();	
	int s2 = sched_getscheduler(changed); 

	if (s2==SCHED_FIFO) printf("Current Scheduling Policy is FIFO");
        else if (s2==SCHED_RR) printf("Current Scheduling Policy is RR");
        else if (s2==SCHED_OTHER) printf("Current Scheduling Policy is SCHED_OTHER");
}


/*
========================================================================================================
Output:

sudo ./a.out
[sudo] password for prajyot-shende:
Scheduling Policy is SCHED_OTHER
Give a input to change policy
1 for Changing to FIFO
2 for Changing to RR
3 for Changing to OTHER
2
Current Scheduling Policy is RR

========================================================================================================
*/
