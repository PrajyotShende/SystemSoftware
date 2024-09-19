/*
========================================================================================================
Name : 20b
Author : Prajyot Shende
Description : Write two programs so that both can communicate by FIFO - Use one way communication.
Date: 12 Sept, 2024.
========================================================================================================
*/


#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

int main() 
{
    while (100000) 
    {
        int a = open("FIFO_20", O_RDONLY);
        char z[100];
        ssize_t size = read(a, z, sizeof(z));
        if (size > 0) 
	{
            z[size] = '\0'; 
            int c = strcmp(z, "exit");
	    if(c == 0) 
	    { 
                close(a);
                break; 
            }
            write(1, z, size); 
            write(1, "\n", 1);
        }

        close(a);
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
