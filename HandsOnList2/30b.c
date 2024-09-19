#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() 
{
	key_t a = ftok(".", 1);
	int b = shmget(a, 1024, 0666 | IPC_CREAT);
	char *c = (char*) shmat(b, NULL, 0);

	printf("Enter data to write to shared memory: ");
	scanf("%[^\n]", c);
	printf("Content written into shared memory: %s\n", c);

	shmdt(c);

	c = (char*) shmat(b, NULL, SHM_RDONLY);
	printf("Memory attached with read-only flag. Content: %s\n", c);

	printf("Attempting to modify content in read-only mode...\n");
	scanf("%[^\n]", c);
	printf("Read-only mode: Modifications are not allowed. Original content remains: %s\n", c);

	shmdt(c);
	shmctl(b, IPC_RMID, NULL);
	printf("Shared memory segment has been removed.\n");

	return 0;
}

