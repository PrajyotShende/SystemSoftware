#include "common1.h"
#include "bank_structures.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int fd = open("admin.txt", O_RDWR);
    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

    struct LoginCredentials credentials[100];
    int b = read(fd, &credentials, sizeof(credentials));
    if (b == -1)
    {
        perror("Error reading file");
        close(fd);
        return 1;
    }
    close(fd);

    for (int i = 0; i < 3; i++)
    {
        // Print login details ensuring null-termination for string fields
        printf("User %d Details:\n", i + 1);
        printf("Username: %.14s\n", credentials[i].username);
        printf("Password: %.14s\n", credentials[i].password);
        printf("\n");
    }

    return 0;
}
