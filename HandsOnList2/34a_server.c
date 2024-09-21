/*
========================================================================================================
Name : 34a_server
Author : Prajyot Shende 
Description : Write a program to create a concurrent server.
        a. use fork
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
	printf("Server socket created\n");
	struct sockaddr_in b, c;
	b.sin_addr.s_addr = htonl(INADDR_ANY);
	b.sin_family = AF_INET;
	b.sin_port = htons(8080);

	int z = bind(a,(struct sockaddr *)&b, sizeof(b));
	if(z==-1)
	{
		printf("Error binding socket\n");
		_exit(1);
	}
	printf("Binding successful!\n");
	int y = listen(a, 3);
	if(y==-1)
	{
		printf("Error listening for connections\n");
		_exit(1);
	}
	printf("waiting for connections...\n");

	while (1000000)
	{
		int d = sizeof(c);
		int e = accept(a, (struct sockaddr *)&c, &d);
		if (e == -1)
		{
			printf("Error accepting connection\n");
			_exit(1);
		}
		else
		{
			int p = fork();
			if(p==0)
			{
				char f[100];
				printf("Enter message from server to client: \n");
				scanf("%[^\n]", f);
				int x = write(e, f, sizeof(f));
				if(x==-1)
				{
					printf("Unable to write data");
				}
				int w = read(e, f, sizeof(f));
				if(w==-1)
				{
					printf("Unable to read data");
				}
				printf("Data received from client: %s\n", f);
				close(e); 
				_exit(0); 
			}
			else
			{
				close(e); 
			}
		}
	}

	close(a);
}


/*
========================================================================================================
Output:
./a.out
Server socket created
Binding successful!
waiting for connections...
Enter message from server to client: 
Hi client I am server
Data received from client: Hi server I am client



==============================================================================================
==========

*/
