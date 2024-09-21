/*
========================================================================================================
Name : 32.b
Author : Prajyot Shende
Description : Write a program to implement semaphore to protect any critical section.
		b. Protect shared memory from concurrent write access.
Date: 12 Sept, 2024.
========================================================================================================
*/

#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/shm.h>
#include <unistd.h>

struct sem_data
{
	int value;
	struct semid_ds *desc;
	unsigned short *array;
	struct seminfo *__buffer;
};

void main()
{
	int e,f,g;
	key_t d;
	struct sem_data h;
	key_t a = ftok(".", 666);
	int b = shmget(a, 1024, IPC_CREAT | 0744);
	if(b==-1)
	{
		b = semget(a,1,IPC_CREAT|0777);
		h.value=1;
        	semctl(b,0,SETVAL,h);
	}
	
	char *c = shmat(b, NULL, 0);

	d = ftok(".", 332);
	if (d == -1)
	{
		printf("Failed to generate key!\n");
		exit(1);
	}

	e = semget(d, 1, 0);
	if (e == -1)
	{
		e = semget(d, 1, IPC_CREAT | 0700);
		if (e == -1)
		{
			printf("Failed to create semaphore!\n");
			exit(1);
		}
		h.value = 1;
		f = semctl(e, 0, SETVAL, h);
		if (f == -1)
		{
			printf("Failed to initialize semaphore!\n");
			exit(1);
		}
	}

	struct sembuf j;
	j.sem_num = 0;
	j.sem_flg = 0;

	printf("Attempting to lock the critical section...\n");

	j.sem_op = -1;
	g = semop(e, &j, 1);
	if (g == -1)
	{
		printf("Error during semaphore operation!\n");
		exit(1);
	}

	printf("Please enter data in critical section:\n");
	scanf("%[^\n]", c);
	printf("Data in shared memory is: %s\n", c);

	j.sem_op = 1;
	g = semop(e, &j, 1);
	if (g == -1)
	{
		printf("Error during semaphore operation!\n");
		exit(1);
	}
}


/*
========================================================================================================
Output:

./a.out
Attempting to lock the critical section...
Please enter data in critical section:
hi bro
Data saved in shared memory is: hi bro

==============================================================================================
==========

*/
