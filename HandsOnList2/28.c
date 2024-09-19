/*
========================================================================================================
Name : 28
Author : Prajyot Shende
Description : Write a program to change the existing message queue permission (use msqid_ds structure).
Date: 12 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>

int main() 
{
	int a = ftok(".", 1);
	int id = msgget(a, 0666 | IPC_CREAT);
	struct msqid_ds i;

	msgctl(id, IPC_STAT, &i);
	printf("Permissions before changing: %o\n", i.msg_perm.mode);

	i.msg_perm.mode = 0677;

	msgctl(id, IPC_SET, &i);
	msgctl(id, IPC_STAT, &i);
	printf("Permissions after changing: %o\n", i.msg_perm.mode);

	return 0;
}


/*
========================================================================================================
Output:

./a.out
Permissions before changing: 666
Permissions after changing: 677


========================================================================================================
*/
