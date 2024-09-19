/*
========================================================================================================
Name : 27.b
Author : Prajyot Shende
Description : Write a program to receive messages from the message queue.
		b. With IPC_NOWAIT as a flag
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



        struct message received_msg;
        int e = msgrcv(id, &received_msg, sizeof(received_msg.b), 1, IPC_NOWAIT);
        if (e == -1)
        {
                perror("msgrcv failed");
                return 1;
        }


        printf("Message received in the queue: %s\n", received_msg.b);
                                                                         
	return 0;
}

/*
========================================================================================================
Output:

./a.out
Message received in the queue: hi bro


========================================================================================================
*/
