/*
========================================================================================================
Name : 17.c
Author : Prajyot Shende
Description : Write a program to execute ls -l | wc.
		c. Use fcntl
Date: 12 Sept, 2024.
========================================================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<fcntl.h>

int main()
{
        int arr[2];
        int a;
        int b = pipe(arr);


        if (b==-1)
        {
                printf("Not able to establish a connection\n");
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
                close(0);
                fcntl(arr[0],F_DUPFD,0);
                close(arr[1]);
                execl("/usr/bin/wc", "wc", NULL);
               
              
        }
        else
        {
                close(1);
                fcntl(arr[1],F_DUPFD,1);
                close(arr[0]);
                execl("/usr/bin/ls", "ls", "-l", NULL);
             

        }
        return 0;
}


/*
========================================================================================================
Output:

./a.out
     65     578    4358


========================================================================================================
*/
