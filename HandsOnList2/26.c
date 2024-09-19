/*
========================================================================================================
Name : 26
Author : Prajyot Shende
Description : Write a program to send messages to the message queue. Check $ipcs -q.
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

/*	struct message received_msg;
	int e = msgrcv(id, &received_msg, sizeof(received_msg.b), 1, 0);
	if (e == -1)
	{
		perror("msgrcv failed");
		return 1;
	}
*/
 	printf("Message sent in the queue: %s\n", msg.b);
	//printf("Message received in the queue: %s\n", received_msg.b);

	return 0;
}



/*
========================================================================================================
Output:

a.out
Enter Text: hi
Message sent in the queue: hi

Message received in the queue: hi


ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages
0x01057bce 1          prajyot-sh 666        100          1

========================================================================================================
*/

