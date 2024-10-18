// #include <stdio.h>
// #include <fcntl.h>
// #include <unistd.h>
// #include <string.h>
// #include <stdlib.h>
// #include <sys/stat.h>
#include "common1.h"
#include "bank_structures.h"


// struct LoginCredentials {
//     char username[15];
//     char password[15];
// };

int main() {
    struct LoginCredentials admin1 = {"admin1", "password1"};
    struct LoginCredentials admin2 = {"admin2", "password2"};
    struct LoginCredentials admin3 = {"admin3", "password3"};

    struct LoginCredentials buff[3];
    buff[0] = admin1;
    buff[1] = admin2;
    buff[2] = admin3;

    int fd = open("admin.txt", O_CREAT | O_RDWR, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return -1;
    }

    int a = write(fd, &buff, sizeof(buff));
    if (a == -1) {
        perror("Error in writing to admin.txt");
    } else {
        printf("Credentials for admin stored successfully!\n");
    }

    close(fd);
    return 0;
}
