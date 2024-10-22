#include "common1.h"
#include "bank_structures.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    // Open the transaction file in read/write mode
    int fd = open("transactions.txt", O_RDWR);
    if (fd == -1)
    {
        perror("Error opening transaction file");
        return 1;
    }

    // Read the file contents into the transaction array
    struct Transaction transactions[100];
    int b = read(fd, &transactions, sizeof(transactions));
    if (b == -1)
    {
        perror("Error reading transaction file");
        close(fd);
        return 1;
    }
    close(fd);

    // Calculate the number of transactions read
    int num_transactions = b / sizeof(struct Transaction);  

    // Loop through the read transactions and print details
    for (int i = 0; i < num_transactions; i++)
    {
        // Print transaction details
        printf("Transaction %d Details:\n", i + 1);
        printf("Transaction ID: %d\n", transactions[i].transaction_id);  // Print the transaction ID
        printf("Customer Account No: %d\n", transactions[i].customer_account_no);  // Print the customer account number
        printf("Amount: %.2f\n", transactions[i].amount);  // Print the transaction amount
        printf("Transaction Type: %d\n", transactions[i].transaction_type);  // Print the transaction type
        printf("Transaction Time: %s", ctime(&transactions[i].transaction_time));  // Print the transaction time
        printf("\n");
    }

    return 0;
}
