/*
========================================================================================================
Name : 33_client
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
	printf("Socket successfully created\n");
	struct sockaddr_in b;
	b.sin_addr.s_addr = htonl(INADDR_ANY);
	b.sin_family = AF_INET;
	b.sin_port = htons(8080);
	int c = connect(a, (struct sockaddr *)&b, sizeof(b));
	if (c == -1)
	{
		printf("Error while establishing connection\n");
		_exit(1);
	}
	printf("Connected to server successfully\n");
	char d[100];
	int n = read(a, d, sizeof(d));
	if (n > 0)
	{
		printf("Data received from server: %s\n", d);
	}
	printf("Enter message for server: ");
	scanf("%[^\n]", d);
	int x = write(a, d, sizeof(d));
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
Connected to server successfully
Data received from server: Hi server, I am client
Enter message for server: Hi client I am server



==============================================================================================
==========
*/

