#include<stdio.h>
#include<sched.h>
int main()
{
	int MAX_PRIORITY_FIFO = sched_get_priority_max(SCHED_FIFO);
	int MIN_PRIORITY_FIFO = sched_get_priority_min(SCHED_FIFO);
	int ROUND_ROBIN_PRIORITY_MAX = sched_get_priority_max(SCHED_RR);
	int ROUND_ROBIN_PRIORITY_MIN = sched_get_priority_min(SCHED_RR);
	printf("FIFO max priority is %d\n", MAX_PRIORITY_FIFO);
	printf("FIFO min priority is %d\n", MIN_PRIORITY_FIFO);
	printf("RR max priority is %d\n", ROUND_ROBIN_PRIORITY_MAX);
	printf("RR min priority is %d\n", ROUND_ROBIN_PRIORITY_MIN);
}
