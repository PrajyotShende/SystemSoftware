/*
========================================================================================================
Name : 20a
Author : Prajyot Shende
Description : Write two programs so that both can communicate by FIFO - Use one way communication.
Date: 12 Sept, 2024.
========================================================================================================
*/

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	int m = mkfifo("FIFO_20", 0666);
	if (m == -1) 
	{
		printf("Unable to create FIFO");
		exit(1);
	}

	char *x = NULL;
	size_t size = 0;

	printf("Enter Text\n");
	printf("To exit submit empty string\n");
	while (1000000) 
	{
		int a = open("FIFO_20", O_WRONLY);
	
		if (a == -1) 
		{
			perror("Unable to open FIFO for writing");
			exit(1);
		}
		printf("Enter message:\n");
	
		int b = getline(&x, &size, stdin);

		if (x[0] == '\n') 
		{
			write(a, "exit", 4);
			close(a);
			break;
		}
		
		write(a, x, b);
		close(a);
		size = 0;
	}

	return 0;
}


/*
========================================================================================================

./a.out
To exit submit empty string
Enter message:
abcd
Enter message:


========================================================================================================
*/
