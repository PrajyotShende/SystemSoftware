/*
========================================================================================================
Name : 7
Author : Prajyot Shende
Description : Write a simple program to print the created thread ids.
Date: 12 Sept, 2024.
========================================================================================================
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* print(void* a)
{
        printf("Thread %d is running has Thread ID :- %lu\n", *((int*)a),pthread_self());
        //exit(1);
}

int main()
{
        pthread_t t[3];
        int z[3];
        int i;
        for(i = 0; i<3; i++)
        {
                z[i] = i;
                int b = pthread_create(&t[i], NULL, print, &z[i]);
                if(b!=0)
                {
                        printf("Some error while creating thread %d\n", i);
                        exit(0);
                }
        }

        for(i = 0; i<3; i++)
        {
                pthread_join(t[i], NULL);
        }

        printf("Joining of threads completed\n");
        return 0;
}


/*
========================================================================================================
Output:

./a.out
Thread 0 is running has Thread ID :- 140539441706688
Thread 1 is running has Thread ID :- 140539433313984
Thread 2 is running has Thread ID :- 140539424921280
Joining of threads completed

========================================================================================================
*/
