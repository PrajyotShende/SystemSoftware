/*
========================================================================================================
Name : 32.c
Author : Prajyot Shende
Description : Write a program to implement semaphore to protect any critical section.
		c. Protect multiple pseudo resources (may be two) using counting semaphore.
Date: 12 Sept, 2024.
========================================================================================================
*/


#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>

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


	d = ftok(".", 333);
	if (d == -1)
	{
		printf("Failed to generate key!\n");
		_exit(1);
	}

	e = semget(d, 1, 0);
	if (e == -1)
	{
		e = semget(d, 1, IPC_CREAT | 0700);
		if (e == -1)
		{
			printf("Failed to create semaphore!\n");
			_exit(1);
		}
		h.value = 2;
		f = semctl(e, 0, SETVAL, h);
		if (f == -1)
		{
			printf("Failed to initialize semaphore!\n");
			_exit(1);
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
		_exit(1);
	}

	printf("Lock acquired!\n");

	printf("Inside critical section. Press Enter to continue...");
	getchar();
	int h_num;
	int fd = open("./32c_ticket.txt", O_RDWR | O_CREAT, S_IRWXU);
	if (fd == -1)
	{
		printf("File open error!\n");
		_exit(1);
	}

	int n = read(fd, &h_num, sizeof(h_num));
	if (n == 0)
	{
		h_num = 1;
	}
	else
	{
		h_num += 1;
		lseek(fd, 0, SEEK_SET);
	}
	write(fd, &h_num, sizeof(h_num));
	printf("Ticket number is: %d\n", h_num);
	printf("Ticket number has been saved to the file.\n");

	j.sem_op = 1;
	g = semop(e, &j, 1);
	if (g == -1)
	{
		printf("Error during semaphore operation!\n");
		_exit(1);
	}
}

/*
========================================================================================================
Output:
./a.out
Attempting to lock the critical section...
Lock acquired!
Inside critical section. Press Enter to continue...
Ticket number is: 1
Ticket number has been saved to the file.

Attempting to lock the critical section...
Lock acquired!
Inside critical section. Press Enter to continue...
Ticket number is: 2
Ticket number has been saved to the file.


==============================================================================================
==========

*/
