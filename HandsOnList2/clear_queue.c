#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
	key_t k;
	int id;
	k = ftok(".", 1);
	if (k == -1)
	{
		perror("ftok failed");
		return 1;
	}

	id = msgget(k, 0666);
	if (id == -1)
	{
		perror("msgget failed");
		return 1;
	}

	if (msgctl(id, IPC_RMID, NULL) == -1)
	{
		perror("msgctl failed");
		return 1;
	}

	printf("Message queue cleared successfully.\n");
	return 0;
}

