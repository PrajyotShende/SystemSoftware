/*
========================================================================================================
Name : 14
Author : Prajyot Shende
Description : Write a simple program to create a pipe, write to the pipe, read from pipe and display on the monitor.
Date: 12 Sept, 2024.
========================================================================================================
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	int arr[2];
	int a;
	char z[] = "Network connection established, ready to send messages\n";
	char y[100];


	int b = pipe(arr);
	if(b==-1) 
	{
		printf("Error in creating connectionthrough pipe");
		exit(1);
	}

	a = fork();

	if(a==-1)
	{
		printf("Unable to create a child process");
		exit(1);
	}
	else if(a==0)
	{
		close(arr[0]);
		write(arr[1],z,sizeof(z));
		close(arr[1]);
		//pritntf("Message sent by child :");
	}
	else
	{
		close(arr[1]);
		read(arr[0],y,sizeof(y));
		printf("Message received from child:- %s",y);
		close(arr[0]);
		exit(0);
	}
}

/*
========================================================================================================
Output:

./a.out
Message received from child:- Network connection established, ready to send messages


========================================================================================================
*/
