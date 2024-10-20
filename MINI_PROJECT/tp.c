#include "common1.h"
#include "bank_structures.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int fd = open("employees.txt", O_RDWR);
    struct BankEmployee credentials[100];
    int b = read(fd, &credentials, sizeof(credentials));
    close(fd);

    for (int i = 0; i < 4; i++)
    {
        printf("Employee %d Details:\n", i + 1);
        printf("Name: %s\n", credentials[i].employee_name);
        printf("ID: %s\n", credentials[i].id);
        printf("Role: %c\n", credentials[i].role);
        printf("Total Loans: %d\n", credentials[i].total_loans);
        printf("Gender: %c\n", credentials[i].gender);
        printf("Age: %d\n", credentials[i].age);
        printf("Username: %s\n", credentials[i].username);
        printf("Password: %s\n", credentials[i].password);

        printf("Loan: ");
        for (int j = 0; j < 10; j++)
        {
            printf("%d ", credentials[i].loan[j]);
        }
        printf("\n\n");
    }

    return 0;
}
