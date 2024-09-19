/*
========================================================================================================
Name : 24
Author : Prajyot Shende
Description : Write a program to create a message queue and print the key and message queue id.
Date: 12 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>

int main() 
{

	long a = ftok(".", 1);
	if (a == -1) 
	{
		printf("Failed ftok");
		return 0;
	}

	printf("Key: %ld\n",a);

	int b = msgget(a,0666|IPC_CREAT);
	if (b == -1) 
	{
		printf("Failed to get Queue ID");
		return 1;
	}
	printf("Queue ID: %d\n", b);
}

/*
========================================================================================================
Output:

./a.out
Key: 17136590
Queue ID: 1

========================================================================================================
*/
