/*
========================================================================================================
Name : 33_server
Author : Prajyot Shende
Description : Write a program to communicate between two machines using socket.
Date: 12 Sept, 2024.
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
	printf("Server socket created\n");
	struct sockaddr_in b, c;
	b.sin_addr.s_addr = htonl(INADDR_ANY);
	b.sin_family = AF_INET;
	b.sin_port = htons(8080);
	int d = bind(a, (struct sockaddr *)&b, sizeof(b));
	if (d == -1)
	{
		printf("Error binding name to socket!\n");
		_exit(1);
	}
	printf("Binding to server socket successful!\n");
	int e = listen(a, 2);
	if (e == -1)
	{
		printf("Error listening for connections\n");
		_exit(1);
	}
	printf("Listening for connections...\n");
	int f = (int)sizeof(c);
	int g = accept(a, (struct sockaddr *)&c, &f);
	if (g == -1)
	{
		printf("Error accepting connection\n");
		_exit(1);
	}
	else
	{
		char h[100];
		printf("Enter message from server to client: ");
		scanf("%[^\n]", h);
		int x = write(g, h, sizeof(h));
		if(x==-1)
        	{
                	printf("Unable to write data");
        	}

		int w = read(g, h, sizeof(h));
		if(w==-1)
        	{
                	printf("Unable to read data");
        	}
		printf("Data received from client: %s\n", h);
	}
	close(a);
}


/*
========================================================================================================
Output:

./a.out
Server socket created
Binding to server socket successful!
Listening for connections...
Enter message from server to client: Hi server, I am client
Data received from client: Hi client I am server


==============================================================================================
==========

*/
