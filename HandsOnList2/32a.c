/*
========================================================================================================
Name : 32.a
Author : Prajyot Shende
Description : Write a program to implement semaphore to protect any critical section.
		a. Rewrite the ticket number creation program using semaphore.
Date: 12 Sept, 2024.
========================================================================================================
*/


#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>

struct a
{
    int a;
    struct semid_ds *b;
    unsigned short int *c;
    struct seminfo *d;
};

int main()
{
       	int b, c, d;
	struct sembuf s;
	struct a x;

	c = open("32_ticket.txt", O_RDWR | O_CREAT, S_IRWXU);
	if (c == -1)
	{
		printf("Unable to open file\n");
		exit(1);
	}


	key_t y = ftok(".",11);
	int z = semget(y, 1, 0);

	if (z == -1)
	{
		z = semget(y, 1, IPC_CREAT | 0700);
		x.a = 1;
		semctl(z, 0, SETVAL, &x);
	}

	s.sem_num = 0;
	s.sem_flg = 0;
	s.sem_op = -1;

	printf("Trying to enter critical section\n");
	semop(z, &s, 1);

	printf("Entered in critical section\n");
	getchar();

	d = read(c, &b, sizeof(b));
	if (d == 0)
	{
		b = 1;
	}
	else if(d==-1)
	{
		printf("Error in reading data");
	}
	else
	{
		b += 1;
		lseek(c, 0, SEEK_SET);
   	}

	int m = write(c, &b, sizeof(b));
	if(m==-1) 
		printf("Cannot wrute the ticket no to file");
	printf("Ticket: %d\n", b);
	printf("Saved to file\n");

	printf("Exiting critical section\n");
	s.sem_op = 1;
	semop(z, &s, 1);

	exit(0);
}


/*
========================================================================================================
Output:
./a.out

Trying to enter critical section
Entered in critical Section

Ticket: 2
Saved to file
Exiting critical section

Trying to enter critical section
Entered in critical Section

Ticket: 3
Saved to file
Exiting critical section

Trying to enter critical section
Entered in critical Section

Ticket: 4
Saved to file
Exiting critical section


==============================================================================================
==========

*/
