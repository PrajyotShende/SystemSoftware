/*
========================================================================================================
Name : 11 
Author : Prajyot Shende
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal - use sigaction system call.
Date: 12 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>

void sig()
{
        printf("\n");
        printf("Interrupt signal was detected\n");
        exit(1);
}


int main()
{
      
        printf("Ignoring SIG_INT\n");
        
	
	struct sigaction ignore,back_to_default;
        
	ignore.sa_handler = SIG_IGN;
        sigemptyset(&ignore.sa_mask);
        sigaction(SIGINT,&ignore,0);

	printf("Try ctrl + c you will not get a interrupt signal for the next 5 seconds\n");

	sleep(5);

	printf("\n");

	printf("Restoring to default function\n");

	back_to_default.sa_handler = SIG_DFL;
        back_to_default.sa_handler = sig;
	sigemptyset(&back_to_default.sa_mask);
        sigaction(SIGINT,&back_to_default,0);
	
	printf("When terminating a process on terminal by using ctrl + c you will get a interrupt signal\n");
	
	while(100000);
        

}


/*
========================================================================================================
Output:

./a.out
Ignoring SIG_INT
Try ctrl + c you will not get a interrupt signal for the next 5 seconds
^C^C^C^C^C
Restoring to default function
When terminating a process on terminal by using ctrl + c you will get a interrupt signal
^C
Interrupt signal was detected


========================================================================================================
*/
