#include "common1.h"
#include "bank_structures.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    // Open the feedback file in read/write mode
    int fd = open("feedback.txt", O_RDWR);
    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

    // Read the file contents into the credentials array
    struct Feedback credentials[100];
    int b = read(fd, &credentials, sizeof(credentials));
    if (b == -1)
    {
        perror("Error reading file");
        close(fd);
        return 1;
    }
    close(fd);

    // Loop through the read feedbacks and print details
    int num_feedbacks = b / sizeof(struct Feedback);  // Calculate the number of feedbacks read
    for (int i = 0; i < num_feedbacks; i++)
    {
        // Print feedback details
        printf("Feedback %d Details:\n", i + 1);
        printf("ID: %d\n", credentials[i].id);  // Print the integer ID
        printf("Feedback: %s\n", credentials[i].feed_back);  // Print the feedback text
        printf("Review: %d\n", credentials[i].review);  // Print the feedback text
        printf("\n");
    }

    return 0;
}
