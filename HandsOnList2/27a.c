/*
========================================================================================================
Name : 27.a
Author : Prajyot Shende
Description : Write a program to receive messages from the message queue.
		a. With 0 as a flag
Date: 12 Sept, 2024.
========================================================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct message
{
	long a;
	char b[100];
};

int main()
{
	key_t k;
	int id;
	struct message msg;
	k = ftok(".", 1);
	if (k == -1)
	{
		perror("ftok failed");
		return 1;
	}

	id = msgget(k, 0666 | IPC_CREAT);
	if (id == -1)
	{
		perror("msgget failed");
		return 1;
	}


	printf("Enter Text: ");
	fgets(msg.b, 100, stdin);
	msg.a = 1;

	int d = msgsnd(id, &msg, sizeof(msg.b), 0);
	if (d == -1)
	{
		perror("msgsnd failed");
		return 1;
	}

	printf("Message sent in the queue: %s\n", msg.b);

	return 0;
}


/*
========================================================================================================
Output:

./a.out
Enter Text: hi bro
Message sent in the queue: hi bro


========================================================================================================
*/
