/*
========================================================================================================
Name : 25
Author : Prajyot Shende
Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures):
		a. access permission
		b. uid, gid
		c. time of last message sent and received
		d. time of last change in the message queue
		e. size of the queue
		f. number of messages in the queue
		g. maximum number of bytes allowed
		h. pid of the msgsnd and msgrcv
Date: 12 Sept, 2024.
========================================================================================================
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

int main()
{
	key_t k;
	int a;
	struct msqid_ds q;

	k = ftok(".", 1);
	if(k == -1)
	{
		perror("Error generating key using ftok");
		return 1;
	}

	a = msgget(k, 0666 | IPC_CREAT);
	if(a==-1)
	{
		perror("Error getting message queue ID");
		return 1;
	}

	int b = msgctl(a, IPC_STAT, &q);
	if (b==-1)
	{
		perror("Error retrieving message queue info");
		return 1;
	}

	int permissions = q.msg_perm.mode;
	int uid = q.msg_perm.uid;
	int gid = q.msg_perm.gid;
	unsigned long curr_size = q.__msg_cbytes;
	unsigned long msg_count = q.msg_qnum;
	unsigned long max_bytes = q.msg_qbytes;
	int sender_pid = q.msg_lspid;
	int receiver_pid = q.msg_lrpid;

	printf("Queue Permissions: %o\n", permissions);
	printf("Owner UID: %d\n", uid);
	printf("Owner GID: %d\n", gid);
	printf("Last Message Sent: %s", ctime(&q.msg_stime));
	printf("Last Message Received: %s", ctime(&q.msg_rtime));
	printf("Last Change: %s", ctime(&q.msg_ctime));
	printf("Current Queue Size (bytes): %lu\n", curr_size);
	printf("Number of Messages in Queue: %lu\n", msg_count);
	printf("Maximum Allowed Bytes: %lu\n", max_bytes);
	printf("PID of Last Sender: %d\n",sender_pid);
	printf("PID of Last Receiver: %d\n",receiver_pid);

	return 0;
}


/*
========================================================================================================
Output:

./a.out
Queue Permissions: 666
Owner UID: 1000
Owner GID: 1000
Last Message Sent: Fri Sep 20 00:02:18 2024
Last Message Received: Fri Sep 20 00:02:25 2024
Last Change: Fri Sep 20 00:02:17 2024
Current Queue Size (bytes): 0
Number of Messages in Queue: 0
Maximum Allowed Bytes: 16384
PID of Last Sender: 5457
PID of Last Receiver: 5463


========================================================================================================
*/
