/*
========================================================================================================
Name : 9
Author : Prajyot Shende
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal - Use signal system call.
Date: 12 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>

void restoring_todefault_action()
{
        printf("\n");
        printf("Interrupt signal was detected\n");
        //signal(SIGINT,SIG_DFL);
	exit(1);
}


int main()
{
        printf("When terminating a process on terminal by using ctrl + c you will get a interrupt signal\n");
        signal(SIGINT, SIG_IGN);

	//getchar();
	sleep(5);


	signal(SIGINT,SIG_DFL);
	signal(SIGINT,restoring_todefault_action);
	//pause();
	//getchar();

        while(10000);

        //getchar();

        //trigger_segfault();

}


/*
========================================================================================================
Output:

./a.out
When terminating a process on terminal by using ctrl + c you will get a interrupt signal
^C^C^C^C
^C
Interrupt signal was detected


========================================================================================================
*/
