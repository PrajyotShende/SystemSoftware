/*
========================================================================================================
Name : 16
Author : Prajyot Shende
Description : Write a program to send and receive data from parent to child vice versa. Use two way communication.
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
	char z[] = "Hi parent I am your child\n";
        char y[] = "Hi Child I am your parent\n";
        char p[100];
	char q[100];


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
		//sleep(1);
		read(arr[0],p,sizeof(p));
		write(arr[1],z,sizeof(z));
                printf("Message received from parent:- %s\n",p);
                close(arr[1]);
		close(arr[0]);
        }
        else
        {
		write(arr[1],y,sizeof(y));
		sleep(1);
        	read(arr[0],q,sizeof(q));
		//write(arr[1],y,sizeof(y));
                close(arr[1]);
                close(arr[0]);
		printf("Message sent by child : %s\n",q);

        }
}

/*
========================================================================================================
Output:

./a.out
Message received from parent:- Hi Child I am your parent

Message sent by child : Hi parent I am your child



========================================================================================================
*/
