/*
========================================================================================================
Name : 30
Author : Prajyot Shende
Description : Write a program to create a shared memory.
		a. write some data to the shared memory
		b. attach with O_RDONLY and check whether you are able to overwrite.
		c. detach the shared memory
		d. remove the shared memory
Date: 19 Sept, 2024.
========================================================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() 
{
	key_t a = ftok(".", 1);
	if(a==-1) 
	{
		perror("ftok failed");
		return 1;
	}

	int b = shmget(a,1024,0666|IPC_CREAT);
	if(b==-1) 
	{
		perror("shmget failed");
		return 1;
	}

	char *c = (char*) shmat(b, NULL, 0);
	if(c==(char*)-1) 
	{
		perror("shmat failed");
		return 1;
	}
	printf("Enter data to write in shared memory: ");
	scanf("%[^\n]", c);
	printf("Shared memory: %s\n", c);
	shmdt(c);
	c = (char*) shmat(b, NULL, SHM_RDONLY);
	if (c==(char*)-1) 
	{
		perror("shmat failed");
		return 1;
	}
	printf("Now with Read-only flag. Content: %s\n", c);
	printf("Trying to change shared memory content in the read-only mode...\n");

	scanf("%[^\n]", c);
	printf("After trying to change the contents of shared memory: %s\n", c);
	shmdt(c);
	shmctl(b, IPC_RMID, NULL);
	printf("Shared memory segment has been removed.\n");
	return 0;
}


/*
========================================================================================================
Output:

./a.out
Enter data to write in shared memory: HI
Shared memory: HI
Now with Read-only flag. Content: HI
Trying to change shared memory content in the read-only mode...
After trying to change the contents of shared memory: HI
Shared memory segment has been removed.


========================================================================================================
*/
