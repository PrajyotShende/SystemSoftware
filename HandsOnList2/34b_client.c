/*
========================================================================================================
Name : 34b_client
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

void main()
{
	int a = socket(AF_INET, SOCK_STREAM, 0);
	if (a == -1)
	{
		printf("Error creating socket\n");
		_exit(1);
	}
	printf("Socket successfully created\n");
	struct sockaddr_in b;
	b.sin_addr.s_addr = htonl(INADDR_ANY);
	b.sin_family = AF_INET;
	b.sin_port = htons(9090);
	int c = connect(a, (struct sockaddr *)&b, sizeof(b));
	if (c == -1)
	{
		printf("Error establishing connection\n");
		_exit(1);
	}
	printf("Connection with server established\n");
	char d[100];
	int w = read(a, d, sizeof(d));
	if(w==-1)
	{
		printf("Unable to read data");
	}
	printf("Data received from server: %s\n", d);
	printf("Enter message for server: \n");
	scanf("%[^\n]", d);
	int x =write(a, d, sizeof(d));
	if(x==-1)
        {
                printf("Unable to write data");
        }

	close(a);
}


/*
========================================================================================================
Output:
./a.out
Socket successfully created
Connection with server established
Data received from server: Hi I am server

Enter message for server: 
Hi bro


==============================================================================================
==========

*/
