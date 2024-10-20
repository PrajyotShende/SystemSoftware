#include "common1.h"
#include "bank_structures.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    // Open the loan file in read/write mode
    int fd = open("loan.txt", O_RDWR);
    if (fd == -1)
    {
        perror("Error opening loan file");
        return 1;
    }

    // Read the file contents into the loan array
    struct Loan loans[100];
    int b = read(fd, &loans, sizeof(loans));
    if (b == -1)
    {
        perror("Error reading loan file");
        close(fd);
        return 1;
    }
    close(fd);

    // Loop through the read loans and print details
    int num_loans = b / sizeof(struct Loan);  // Calculate the number of loans read
    for (int i = 0; i < num_loans; i++)
    {
        // Print loan details
        printf("Loan %d Details:\n", i + 1);
        printf("Loan ID: %d\n", loans[i].loanId);  // Print the loan ID
        printf("Amount: %.2f\n", loans[i].amount);  // Print the loan amount
        printf("Customer Account No: %d\n", loans[i].customer_acc_no);  // Print the customer account number
        printf("Employee ID: %s\n", loans[i].employee_ID);  // Print the employee ID handling the loan
        printf("Loan Status: %d\n", loans[i].loanStatus);  // Print the loan status
        printf("\n");
    }

    return 0;
}



