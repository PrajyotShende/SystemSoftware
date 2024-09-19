/*
========================================================================================================
Name : 21b
Author : Prajyot Shende
Description : Write two programs so that both can communicate by FIFO - Use two way communications.
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
        char x[100];
        size_t size = 0;

        //printf("Enter Text\n");
        int a = open("FIFO_21a", O_RDONLY);
        if (a == -1)
        {
                perror("Unable to open FIFO for writing");
                exit(1);
        }
        int b = read(a, x, sizeof(x));
        x[b] = '\0';
	printf("Message received : %s\n",x);
	close(a);


        int c = open("FIFO_21b", O_WRONLY);
        if (c == -1)
        {
                perror("Unable to open FIFO for writing");
                exit(1);
        }
        char y[] = "Hi boss,I am your underling";
        write(c, y, sizeof(y));
        close(c);
        

        return 0;
}

/*
========================================================================================================
Output:

./a.out
Message received : Hi,I am the boss

========================================================================================================
*/
