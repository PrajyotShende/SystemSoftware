/*
========================================================================================================
Name : 31
Author : Prajyot Shende
Description : Write a program to create a semaphore and initialize value to the semaphore.
		a. Create a binary semaphore.
Date: 12 Sept, 2024.
========================================================================================================
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>

struct semaphore
{
    int a;
    struct semid_ds *b;
    unsigned short int *c;
};

int main()
{
    struct semaphore x;
    key_t y = ftok(".", 1);
    int z = semget(y, 1, IPC_CREAT | 0744);
    x.a = 1;
    printf("Binary Semaphore initialized\n");
    semctl(z, 0, SETVAL, x);

    struct semaphore u;
    key_t v = ftok(".", 2);
    int w = semget(v, 1, IPC_CREAT | 0744);
    u.a = 5;
    printf("Counting Semaphore set with value: %d\n", u.a);
    semctl(w, 0, SETVAL, u);

    return 0;
}


/*
========================================================================================================
Output:
./a.out
Semaphore initialized
Semaphore set with value: 10


==============================================================================================
==========

*/
