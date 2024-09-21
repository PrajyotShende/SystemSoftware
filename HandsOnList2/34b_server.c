/*
========================================================================================================
Name : 34b_server
Author : Prajyot Shende 
Description : Write a program to create a concurrent server.
        b. use pthread_create
Date: 20 Sept, 2024.
========================================================================================================
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *client_handler(void *ptr)
{
	int *sock_ptr = (int *)ptr;
	char msg[128];
	write(*sock_ptr, "Hi I am server\n", 22);
	read(*sock_ptr, msg, sizeof(msg));
	printf("Received from client: %s\n", msg);
	close(*sock_ptr);
	return NULL;
}

int main()
{
	int a = socket(AF_INET, SOCK_STREAM, 0);
	if (a < 0)
	{
		printf("Error creating socket\n");
		return 1;
	}
	printf("Server socket created\n");

	struct sockaddr_in b, c;
	b.sin_addr.s_addr = htonl(INADDR_ANY);
	b.sin_family = AF_INET;
	b.sin_port = htons(9090);
	
	int p = bind(a, (struct sockaddr *)&b, sizeof(b));
        if(p<0)	
	{
		printf("Binding error\n");
		close(a);
		return 1;
	}
	printf("Binding successful!\n");

	int q = listen(a, 5);
	if(q< 0)
	{
		printf("Error listening for connections\n");
		close(a);
		return 1;
	}
	printf("Waiting for client connections...\n");
	while (1000000)
	{
		socklen_t d = sizeof(c);
		int e = accept(a, (struct sockaddr *)&c, &d);
		if (e < 0)
		{
			printf("Error accepting connection\n");
			continue;
		}
		else
		{
			pthread_t f;
			int r = pthread_create(&f, NULL, client_handler, (void *)&e);
		        if(r!=0)	
			{
				printf("Thread creation error\n");
				close(e);
			}
			pthread_detach(f);
		}
	}

	close(a);
	return 0;
}
/*
========================================================================================================
Output:
./a.out
Server socket created
Binding successful!
Waiting for client connections...
Received from client: Hi bro


==============================================================================================
==========

*/
