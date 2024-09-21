/*
========================================================================================================
Name : 32.d
Author : Prajyot Shende
Description : Write a program to implement semaphore to protect any critical section.
		d. Remove the created semaphore.
Date: 12 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/sem.h>
#include<sys/ipc.h>
int main()
{
	int z;
	printf("Enter the semaphore no you would like to delete");
	scanf("%d",&z);

	int a = ftok(".", z);
	
	if(a == -1)
	{
		perror("error while ftok");
	}
	
	int b = semget(a, 1, IPC_CREAT | 0777);
	if(b == -1)
	{
		perror("error while creating semaphore");
	}
	
		
	int c = semctl(b, 0, IPC_RMID);
	
	if(c == -1)
	{
		perror("error while deleting semaphore\n");
	}
	else
	{
		printf("semaphore deleted successfully\n");
	}
	return 0;
}

/*
========================================================================================================
Output:
./a.out
Enter the semaphore no you would like to delete 331
semaphore deleted successfully

==============================================================================================
==========

*/
