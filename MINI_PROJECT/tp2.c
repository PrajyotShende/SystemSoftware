#include "common1.h"
#include "bank_structures.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int fd = open("customers.txt", O_RDWR);
    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

    struct Customer credentials[100];
    int b = read(fd, &credentials, sizeof(credentials));
    if (b == -1)
    {
        perror("Error reading file");
        close(fd);
        return 1;
    }
    close(fd);

    for (int i = 0; i < 4; i++)
    {
        // Print customer details ensuring proper data usage
        printf("Customer %d Details:\n", i + 1);
        
        printf("Name: %.49s\n", credentials[i].customer_name);
        printf("Account Number: %d\n", credentials[i].acc_no);
        printf("Gender: %c\n", credentials[i].gender);
        printf("Age: %d\n", credentials[i].age);
        printf("Balance: %.2f\n", credentials[i].balance);
        printf("Account Active: %s\n", credentials[i].active ? "Yes" : "No");
        printf("Loan ID: %d\n", credentials[i].loanID);
        printf("Username: %.14s\n", credentials[i].username);
        printf("Password: %.14s\n", credentials[i].password);
        printf("Last transaction: %d.\n", credentials[i].last_transaction);

        printf("Transactions: ");
        // for (int j = 0; j < 15; j++)
        // {
        //     printf("%d ", credentials[i].transaction[j]);
        // }
        // printf("\n\n");
    
                // printf("Loans: ");
        for (int j = 0; j < 10; j++)
        {
            printf("%d ", credentials[i].transaction[j]);
        }
        printf("\n\n");
    
    
    }

    return 0;
}
