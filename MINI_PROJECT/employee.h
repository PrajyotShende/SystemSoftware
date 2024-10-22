#ifndef EMPLOYEE
#define EMPLOYEE

#include "common1.h"
#include "bank_structures.h"

int lock_Employee1(int socket_fd,int fd, int number);
void unlock_Employee1(int socket_fd,int fd, int number);
void changePassword_Employee(int socket_fd,int fd, int number);
int Checking_login_credentials_Employee(int socket_fd,const char *input_username, const char *input_password, int *number);
void login_employee(int socket_fd);
void add_customer(int socket_fd);
int is_acc_Unique(int fd,int a);
void Modify_Customer_Details1(int socket_fd);
int lock_Customer1(int socket_fd,int fd, int number);
void unlock_Customer1(int socket_fd,int fd, int number);
void activate_deactivate_customers(int socket_fd);

int lock_Loan(int fd, int loan_index) 
{
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = loan_index * sizeof(struct Loan);
    lock.l_len = sizeof(struct Loan);
    return (fcntl(fd, F_SETLKW, &lock) == -1) ? 0 : 1;
}

void unlock_Loan(int fd, int loan_index) 
{
    struct flock lock;
    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = loan_index * sizeof(struct Loan);
    lock.l_len = sizeof(struct Loan);
    // return (fcntl(fd, F_SETLKW, &lock) == -1) ? 0 : 1;
}

void approve_reject_loans(int socket_fd, int number)
{

    int m;

    int fd_loan = open("loan.txt", O_RDWR);
    if (fd_loan == -1)
    {
        perror("Error opening loan file");
        return;
    }

    int fd_emp = open("employees.txt", O_RDWR);
    if (fd_emp == -1)
    {
        perror("Error opening employee file");
        close(fd_loan);
        return;
    }

    int fd_cust = open("customers.txt", O_RDWR);
    if (fd_cust == -1)
    {
        perror("Error opening customer file");
        close(fd_loan);
        close(fd_emp);
        return;
    }

    char temp_buffer[200], read_buffer[1000], write_buffer[1000];
    int write_bytes, read_bytes;
    memset(read_buffer, 0, sizeof(read_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));

    struct Loan loans[100];
    struct BankEmployee employees[100];
    struct Customer customers[100];

    // int z = lock_Employee1(socket_fd,fd_emp,number);

    read(fd_emp, &employees, sizeof(employees));
    read(fd_loan, &loans, sizeof(loans));
    read(fd_cust, &customers, sizeof(customers));

    if (employees[number].total_loans > 0)
    {
        strcpy(write_buffer, "\nLoans assigned to you:\n");
        for (int i = 0; i < 10; i++)
        {
            if (employees[number].loan[i] != -1)
            {
                int a = employees[number].loan[i];
                for (int j = 0; j < 100; j++)
                {
                    if (loans[j].loanId == a && loans[j].loanStatus == 1)
                    {
                        sprintf(temp_buffer, "Loan ID: %d || Amount: %.2f || Customer Account No: %d || Loan Status: %d\n",
                                loans[j].loanId, loans[j].amount, loans[j].customer_acc_no, loans[j].loanStatus);
                        strcat(write_buffer, temp_buffer);
                    }
                }
            }
        }

        strcat(write_buffer, "%");
        write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
        if (write_bytes == -1)
        {
            perror("Error writing to socket");
            return;
        }

        memset(read_buffer, 0, sizeof(read_buffer));
        strcpy(write_buffer, "\nEnter the Loan ID you want to process: ");
        write(socket_fd, write_buffer, sizeof(write_buffer));
        read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));
        int loan_id = atoi(read_buffer);

        int loan_exists = 0;
        for (int j = 0; j < 100; j++)
        {
            if (loans[j].loanId == loan_id && loans[j].loanStatus == 1)
            {
                loan_exists = 1;
                break;
            }
        }

        if (loan_exists == 0)
        {
            strcpy(write_buffer, "\nThe entered Loan ID does not exist or is not assigned to you.%");
            write(socket_fd, write_buffer, sizeof(write_buffer));
            return;
        }

        int loan_index = -1;
        for (int i = 0; i < 10; i++)
        {
            if (employees[number].loan[i] == loan_id)
            {
                loan_index = i;
                break;
            }
        }

        if (loan_index == -1)
        {
            strcpy(write_buffer, "\nThe entered Loan ID is not assigned to you.%");
            write(socket_fd, write_buffer, sizeof(write_buffer));
            return;
        }

        for (int j = 0; j < 100; j++)
        {
            if (loans[j].loanId == loan_id)
            {
                int z = loan_id;
                for(m = 0; m < 100; m++)
                {
                    if (customers[m].loanID == loan_id)
                    {
                        int m1 = lock_Customer1(socket_fd,fd_cust,m);
                        break;
                    }
                }

                strcpy(write_buffer, "\nDo you want to approve (1) or reject (2) this loan? ");
                write(socket_fd, write_buffer, sizeof(write_buffer));
                memset(read_buffer, 0, sizeof(read_buffer));
                read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));
                int choice = atoi(read_buffer);

                if (choice == 1)  
                {
                    loans[j].loanStatus = 2;
                    for (int k = 0; k < 100; k++)
                    {
                        if (customers[k].acc_no == loans[j].customer_acc_no)
                        {
                            customers[k].balance += loans[j].amount;
                            customers[k].loanID = -1;
                            lseek(fd_cust, k * sizeof(struct Customer), SEEK_SET);
                            write(fd_cust, &customers[k], sizeof(struct Customer));

                            int fd_transaction = open("transactions.txt",O_CREAT|O_RDWR,0666);
                            struct Transaction loan_approval;
                            read(fd_transaction,&loan_approval,sizeof(loan_approval));

                            int f = lseek(fd_transaction,0,SEEK_END);
                            loan_approval.amount = loans[j].amount;
                            loan_approval.customer_account_no = customers[k].acc_no;
                            loan_approval.transaction_type = 5;
                            loan_approval.transaction_time = time(NULL);
                            loan_approval.transaction_id = (f/sizeof(struct Transaction)) + 1;
                            write(fd_transaction, &loan_approval, sizeof(loan_approval));

                            if (customers[k].last_transaction == -1) 
                            {
                                customers[k].last_transaction = 0;
                                customers[k].transaction[0] = loan_approval.transaction_id;
                            } 
                            else 
                            {
                                int last_index = customers[k].last_transaction;
                                customers[k].transaction[(last_index + 1) % 10] = loan_approval.transaction_id;
                                customers[k].last_transaction = (last_index + 1) % 10;
                            }

                            lseek(fd_cust, k * sizeof(struct Customer), SEEK_SET);
                            write(fd_cust, &customers[k], sizeof(struct Customer));

                            break;
                        }
                    }
                    strcpy(write_buffer, "\nLoan approved successfully.%");
                }
                else if (choice == 2)  
                {
                    loans[j].loanStatus = -1;
                    for (int k = 0; k < 100; k++)
                    {
                        if (customers[k].acc_no == loans[j].customer_acc_no)
                        {
                            customers[k].loanID = -1;
                            lseek(fd_cust, k * sizeof(struct Customer), SEEK_SET);
                            write(fd_cust, &customers[k], sizeof(struct Customer));
                            break;
                        }
                    }
                    strcpy(write_buffer, "\nLoan rejected successfully.%");
                }
                else
                {
                    strcpy(write_buffer, "\nInvalid choice.%");
                }

                lseek(fd_loan, j * sizeof(struct Loan), SEEK_SET);
                write(fd_loan, &loans[j], sizeof(struct Loan));

                employees[number].loan[loan_index] = -1;
                employees[number].total_loans--;

                lseek(fd_emp, number * sizeof(struct BankEmployee), SEEK_SET);
                write(fd_emp, &employees[number], sizeof(struct BankEmployee));

                write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
                break;
            }
        }
    }
    else
    {
        strcpy(write_buffer, "\nNo loans assigned to you.%");
        write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
    }

    // unlock_Employee1(socket_fd,fd_emp,number);

    unlock_Customer1(socket_fd,fd_cust,m);


}

void view_assigned_loans(int socket_fd, int number)
{
    int fd = open("loan.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening loan file");
        return;
    }

    struct flock lock;
    memset(&lock, 0, sizeof(lock));
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;

    if (fcntl(fd, F_SETLKW, &lock) == -1)
    {
        perror("Error locking the loan file for reading");
        close(fd);
        return;
    }

    int fd1 = open("employees.txt", O_RDONLY);
    if (fd1 == -1)
    {
        perror("Error opening employee file");
        close(fd);
        return;
    }

    char temp_buffer[200];
    int write_bytes, read_bytes;
    char read_buffer[1000], write_buffer[1000];
    memset(read_buffer, 0, sizeof(read_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));

    struct Loan loans[100];
    struct BankEmployee employees[100];

    read(fd1, &employees, sizeof(employees));
    read(fd, &loans, sizeof(loans));

    if (employees[number].total_loans > 0)
    {
        strcpy(write_buffer, "\nLoans assigned to you:\n");

        for (int i = 0; i < 10; i++)
        {
            if (employees[number].loan[i] != -1)
            {
                int a = employees[number].loan[i];
                for (int j = 0; j < 100; j++)
                {
                    if (loans[j].loanId == a && loans[j].loanStatus == 1)
                    {
                        sprintf(temp_buffer, "Loan ID: %d || Amount: %.2f || Customer Account No: %d || Loan Status: %d\n",
                                loans[j].loanId, loans[j].amount, loans[j].customer_acc_no, loans[j].loanStatus);
                        strcat(write_buffer, temp_buffer);
                        break;
                    }
                }
            }
        }
        strcat(write_buffer, "%");
        write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
        if (write_bytes == -1)
        {
            perror("Error writing to socket");
        }
    }
    else
    {
        strcpy(write_buffer, "\nNo loans assigned to you.%");
        write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
    }

    lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLKW, &lock) == -1)
    {
        perror("Error unlocking the loan file");
    }

    close(fd);
    close(fd1);
}

int is_loan_Unique(int fd, int a, int last)
{
    struct Loan loan_assignment[last];
    lseek(fd, 0, SEEK_SET);

    int b = read(fd, &loan_assignment, sizeof(loan_assignment));
    if (b == -1)
    {
        perror("Error reading file");
        return -1;
    }

    for (int i = 0; i < last; i++)
    {
        if (a == loan_assignment[i].loanId)
        {
            if (loan_assignment[i].loanStatus == 0) 
                return i;
        }
    }

    return -1;
}

void assign_loan_applications(int socket_fd)
{
    int fd = open("loan.txt", O_RDWR);
    if (fd == -1)
    {
        perror("Error Opening File");
        return;
    }

    struct flock lock;
    memset(&lock, 0, sizeof(lock));
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;

    if (fcntl(fd, F_SETLKW, &lock) == -1)
    {
        perror("Error locking the loan file");
        close(fd);
        return;
    }

    int write_bytes, read_bytes;
    char read_buffer[1000], write_buffer[1000];
    memset(read_buffer, 0, sizeof(read_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));

    int file_size = lseek(fd, 0, SEEK_END);
    int last_loan = file_size / sizeof(struct Loan);

    if (last_loan == 0)
    {
        strcpy(write_buffer, "\nNo loans to assign%");
        write(socket_fd, write_buffer, sizeof(write_buffer));
        memset(write_buffer, 0, sizeof(write_buffer));
        close(fd);
        return;
    }

    struct Loan loan_assignment[last_loan];
    lseek(fd, 0, SEEK_SET);
    int b = read(fd, &loan_assignment, sizeof(loan_assignment));
    if (b == -1)
    {
        perror("Error reading file");
        close(fd);
        return;
    }

    strcpy(write_buffer, "\nThese are the list of loans, which have to be assigned:");
    int count = 0;
    for (int k = 0; k < last_loan; k++)
    {
        if (loan_assignment[k].loanStatus == 0)
        {
            count++;
            char temp_buffer[50], temp_buffer1[50], temp_buffer2[50];
            strcat(write_buffer, "\n");

            sprintf(temp_buffer, "%d", loan_assignment[k].loanId);
            strcat(write_buffer, "ID: ");
            strcat(write_buffer, temp_buffer);
            strcat(write_buffer, " || Loan Amount: ");
            sprintf(temp_buffer1, "%f", loan_assignment[k].amount);
            strcat(write_buffer, temp_buffer1);
            strcat(write_buffer, " || Customer Account No. : ");
            sprintf(temp_buffer2, "%d", loan_assignment[k].customer_acc_no);
            strcat(write_buffer, temp_buffer2);
            strcat(write_buffer, "%");
            write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
            memset(write_buffer, 0, sizeof(write_buffer));
        }
    }

    memset(write_buffer, 0, sizeof(write_buffer));

    while (1)
    {
        if (count == 0)
        {
            strcpy(write_buffer, "\nNo loans to assign%");
            write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
            memset(write_buffer, 0, sizeof(write_buffer));
            break;
        }

        strcpy(write_buffer, "\nEnter the loan id you want to assign: ");
        write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
        memset(write_buffer, 0, sizeof(write_buffer));

        read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));
        int z = atoi(read_buffer);
        memset(read_buffer, 0, sizeof(read_buffer));

        if (z == 0)
        {
            strcpy(write_buffer, "\nWrong Loan_ID.%");
            write(socket_fd, write_buffer, sizeof(write_buffer));
            memset(write_buffer, 0, sizeof(write_buffer));
            continue;
        }

        int flag = is_loan_Unique(fd, z, last_loan);

        if (flag >= 0)
        {
            int fd1 = open("employees.txt", O_RDWR);
            if (fd1 == -1)
            {
                perror("Error opening file");
                close(fd);
                return;
            }

            struct BankEmployee new[100];
            read(fd1, &new, sizeof(new));

            while (1)
            {
                strcpy(write_buffer, "\nEnter Employee ID :- ");
                write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
                memset(write_buffer, 0, sizeof(write_buffer));

                read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));

                if (strcmp(read_buffer, "0") == 0)
                {
                    strcpy(write_buffer, "\nInvalid Employee ID. Cannot be zero.%");
                    write(socket_fd, write_buffer, sizeof(write_buffer));
                    memset(write_buffer, 0, sizeof(write_buffer));
                    continue;
                }
                int man = 0;
                int employee_found = 0;
                for (int i = 0; i < 100; i++)
                {
                    if (strcmp(new[i].id, read_buffer) == 0)
                    {
                        if (new[i].role == '1')
                        {
                            strcpy(write_buffer, "\nCannot assign loan to a Manager%");
                            man = 1;
                            write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
                            memset(write_buffer, 0, sizeof(write_buffer));
                            break;
                        }
                        employee_found = 1;

                        // int l = lock_Employee(socket_fd, fd, i);

                        // if (l == 0)
                        // {
                        //     strcpy(write_buffer, "\nCannot currently assign loan to Employee ");
                        //     strcat(write_buffer, read_buffer);
                        //     strcat(write_buffer, "%");
                        //     write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
                        //     memset(write_buffer, 0, sizeof(write_buffer));
                        //     break;
                        // }

                        int a = -1;
                        for (int j = 0; j < 10; j++)
                        {
                            if (new[i].loan[j] == -1)
                            {
                                a = j;
                                break;
                            }
                        }

                        if (new[i].total_loans == 10)
                        {
                            strcpy(write_buffer, "\nNo more loans can be assigned to Employee ");
                            strcat(write_buffer, read_buffer);
                            strcat(write_buffer, "%");
                            write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
                            memset(write_buffer, 0, sizeof(write_buffer));
                            continue;
                        }

                        new[i].loan[a] = loan_assignment[flag].loanId;
                        new[i].total_loans += 1;
                        lseek(fd1, i * sizeof(struct BankEmployee), SEEK_SET);
                        write(fd1, &new[i], sizeof(struct BankEmployee));

                        strcpy(write_buffer, "\nLoan assigned to Employee ");
                        strcat(write_buffer, read_buffer);
                        strcat(write_buffer, " Successfully");
                        strcat(write_buffer, "%");
                        write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
                        memset(write_buffer, 0, sizeof(write_buffer));

                        strcpy(loan_assignment[flag].employee_ID, read_buffer);
                        loan_assignment[flag].loanStatus = 1;
                        lseek(fd, flag * sizeof(struct Loan), SEEK_SET);
                        write(fd, &loan_assignment[flag], sizeof(struct Loan));

                        close(fd1);
                        close(fd);
                        return;
                    }
                }

                if (!employee_found)
                {
                    if (man == 0)
                    {
                        strcpy(write_buffer, "\nNo Employee with ID ");
                        strcat(write_buffer, read_buffer);
                        strcat(write_buffer, "%");
                        write(socket_fd, write_buffer, sizeof(write_buffer));
                        memset(write_buffer, 0, sizeof(write_buffer));
                    }
                }
            }
        }
        else
        {
            strcpy(write_buffer, "\nNo such ID exists. Try again.%");
            write(socket_fd, write_buffer, sizeof(write_buffer));
            memset(write_buffer, 0, sizeof(write_buffer));
        }
    }

    lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLKW, &lock) == -1)
    {
        perror("Error unlocking the loan file");
    }
    
    close(fd);
}

int is_feedback_Unique(int fd, int a,int last)
{
    struct Feedback feedback_review[last];
    lseek(fd, 0, SEEK_SET);  

    int b = read(fd, &feedback_review, sizeof(feedback_review));
    if (b == -1) 
    {
        perror("Error reading file");
        return -1;
    }

    for (int i = 0; i < last; i++)
    {
        if (a == feedback_review[i].id)
        {
            if(feedback_review[i].review == false)
                return i;  
        }
    }

    return -1;  
}

void review_customer_feedback(int socket_fd)
{
    int fd = open("feedback.txt", O_RDWR);
    if (fd == -1)
    {
        perror("Error opening feedback file");
        return;
    }

    struct flock lock;
    memset(&lock, 0, sizeof(lock));
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;

    if (fcntl(fd, F_SETLKW, &lock) == -1)
    {
        perror("Error locking the feedback file");
        close(fd);
        return;
    }

    int write_bytes, read_bytes;
    char read_buffer[1000], write_buffer[1000];
    memset(read_buffer, 0, sizeof(read_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));

    int file_size = lseek(fd, 0, SEEK_END);
    int last = file_size / sizeof(struct Feedback);

    if (last == 0)
    {
        strcpy(write_buffer, "\nNo feedbacks to review%.");
        write(socket_fd, write_buffer, sizeof(write_buffer));
        memset(write_buffer, 0, sizeof(write_buffer));
        close(fd);
        return;
    }

    struct Feedback review[last];
    lseek(fd, 0, SEEK_SET);
    int b = read(fd, &review, sizeof(review));
    if (b == -1)
    {
        perror("Error reading feedback file");
        close(fd);
        return;
    }

    strcpy(write_buffer, "\nThese are the list of feedbacks, which have to be reviewed:");

    int count = 0;
    for (int i = 0; i < last; i++)
    {
        if (review[i].review == false)
        {
            count++;
            char temp_buffer[50];
            strcat(write_buffer, "\n");

            sprintf(temp_buffer, "%d", review[i].id);
            strcat(write_buffer, "ID: ");
            strcat(write_buffer, temp_buffer);
            strcat(write_buffer, " || Feedback: ");
            strcat(write_buffer, review[i].feed_back);
            strcat(write_buffer, "%");
            write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
            memset(write_buffer, 0, sizeof(write_buffer));
        }
    }

    memset(write_buffer, 0, sizeof(write_buffer));

    while (1)
    {
        if (count == 0)
        {
            strcpy(write_buffer, "\nNo feedbacks to review%");
            write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
            memset(write_buffer, 0, sizeof(write_buffer));
            break;
        }

        strcpy(write_buffer, "\nEnter the id of feedback you want to review: ");
        write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
        memset(write_buffer, 0, sizeof(write_buffer));

        read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));
        int a = atoi(read_buffer);
        memset(read_buffer, 0, sizeof(read_buffer));

        if (a == 0)
        {
            strcpy(write_buffer, "\nTry something different.%");
            write(socket_fd, write_buffer, sizeof(write_buffer));
            memset(write_buffer, 0, sizeof(write_buffer));
            continue;
        }

        int flag = is_feedback_Unique(fd, a, last);
        if (flag >= 0)
        {
            review[flag].review = true;

            lseek(fd, flag * sizeof(struct Feedback), SEEK_SET);
            write(fd, &review[flag], sizeof(struct Feedback));

            strcpy(write_buffer, "\nFeedback reviewed successfully.%");
            write(socket_fd, write_buffer, sizeof(write_buffer));
            break;
        }
        else
        {
            strcpy(write_buffer, "\nNo such ID exists. Try again.%");
            write(socket_fd, write_buffer, sizeof(write_buffer));
            memset(write_buffer, 0, sizeof(write_buffer));
        }
    }

    lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLKW, &lock) == -1)
    {
        perror("Error unlocking the feedback file");
    }

    close(fd);
}

void activate_deactivate_customers(int socket_fd)
{

    int write_bytes, read_bytes;
    char read_buffer[1000], write_buffer[1000];
    memset(read_buffer, 0, sizeof(read_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));

    int fd = open("customers.txt",O_RDWR);
    if(fd == -1)
    {
        perror("Error opening file");
    }

    struct Customer newcust[100];
    
    int b = read(fd,&newcust,sizeof(newcust));

    while(1)
    {
            strcpy(write_buffer,"\nEnter Customer Account no :- ");
            write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
            memset(write_buffer, 0, sizeof(write_buffer));
            read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));
            int acc = atoi(read_buffer);
            if (acc == 0)
            {
                strcpy(write_buffer, "\nInvalid account number.%");
                write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
                memset(write_buffer, 0, sizeof(write_buffer));
                continue;  
            }
            for(int i=0;i<100;i++)
            {   
                
                if(newcust[i].acc_no == acc)
                {
                    int l = lock_Customer1(socket_fd,fd, i);
                    if(l == 0) 
                    {
                        strcpy(write_buffer,"\nCannot currently change Customer ");
                        strcat(write_buffer,read_buffer);
                        strcat(write_buffer," Account status");
                        strcat(write_buffer,"%");
                        write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));   
                        return;
                    }
                    memset(read_buffer, 0, sizeof(read_buffer));
                    memset(write_buffer, 0, sizeof(write_buffer));

                    strcpy(write_buffer,"\nThese are customer details \nName of Customer :- ");
                        strcat(write_buffer,newcust[i].customer_name);
                        
                        char temp_buffer[10];  
                        
                        strcat(write_buffer,"\nAge of Customer :- ");
                        sprintf(temp_buffer, "%d", newcust[i].age);  
                        strcat(write_buffer, temp_buffer);

                        temp_buffer[0] = newcust[i].gender;
                        temp_buffer[1] = '\0';  
                        strcat(write_buffer, "\nGender of Customer :- ");
                        strcat(write_buffer, temp_buffer);
                        // strcat(write_buffer, "\n");

                        strcat(write_buffer,"%");
                        write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
                        memset(write_buffer, 0, sizeof(write_buffer));

                        // if(newcust[i].active == true)
                        // {
                        //     strcpy(write_buffer, "Account is currently Active%.");
                        //     write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
                        //     memset(write_buffer, 0, sizeof(write_buffer));
                        // }
                        // else
                        // {
                        //     strcpy(write_buffer, "Account is currently Deactivated%");
                        //     write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
                        //     memset(write_buffer, 0, sizeof(write_buffer));
                        // }
                        

                        // strcpy(write_buffer,"\nWhat do you want to Modify :- \n1. Name\n2. Age\n3. Gender\n4. Account active status\n5. Exit");
                        // write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
                        // memset(write_buffer, 0, sizeof(write_buffer));
                        // read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));
                        // int choice = atoi(read_buffer);
                        // memset(read_buffer, 0, sizeof(read_buffer));

                                if(newcust[i].active == true)
                                {
                                    strcpy(write_buffer, "\nAccount is currently Active.\nDo you want to deactivate it (y/n)");
                                    write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
                                    memset(write_buffer, 0, sizeof(write_buffer));

                                    read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));
                                    read_buffer[strcspn(read_buffer, "\n")] = 0;

                                    if(read_buffer[0] == 'y' || read_buffer[0] == 'Y')
                                    {
                                        newcust[i].active = false;
                                        lseek(fd, i * sizeof(struct Customer), SEEK_SET);
                                        write(fd, &newcust[i], sizeof(struct Customer));
                                        strcpy(write_buffer, "\nSuccessfully Deactivated the customer's account%");
                                        write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
                                        memset(write_buffer, 0, sizeof(write_buffer));
                                        unlock_Customer1(socket_fd, fd, i);                    
                                        return;
                                    }
                                }
                                else if(newcust[i].active == false)
                                {
                                    strcpy(write_buffer, "\nAccount is currently Deactivated.\nDo you want to activate it (y/n)");
                                    write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
                                    memset(write_buffer, 0, sizeof(write_buffer));

                                    read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));
                                    // Trim newlines or extra characters
                                    read_buffer[strcspn(read_buffer, "\n")] = 0;

                                    if(read_buffer[0] == 'y' || read_buffer[0] == 'Y')
                                    {
                                        newcust[i].active = true;
                                        lseek(fd, i * sizeof(struct Customer), SEEK_SET);
                                        write(fd, &newcust[i], sizeof(struct Customer));
                                        strcpy(write_buffer, "\nSuccessfully Activated the customer's account%");
                                        write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
                                        memset(write_buffer, 0, sizeof(write_buffer));
                                        unlock_Customer1(socket_fd, fd, i);
                                        return;
                                    }
                                }
                    unlock_Customer1(socket_fd, fd, i);
                    return;
            
                }
                        
                    
                
            }

            strcpy(write_buffer,"\nNo Customer with Account no. ");
            strcat(write_buffer,read_buffer);
            strcat(write_buffer,"%");
            write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
            memset(write_buffer, 0, sizeof(write_buffer));
            memset(read_buffer, 0, sizeof(read_buffer));

    }
    
    
}

int lock_Customer1(int socket_fd,int fd, int number) 
{
    int write_bytes, read_bytes;
    char read_buffer[1000], write_buffer[1000];
    memset(read_buffer, 0, sizeof(read_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));

    struct flock Admin_WRITELOCK;
    Admin_WRITELOCK.l_type = F_WRLCK;
    Admin_WRITELOCK.l_whence = SEEK_SET;
    Admin_WRITELOCK.l_start = number * sizeof(struct Customer);
    Admin_WRITELOCK.l_len = sizeof(struct Customer);

    int locking = fcntl(fd, F_SETLKW, &Admin_WRITELOCK);

    if (locking == -1) 
    {
        return 0;
    }
    
    return 1;
}

void unlock_Customer1(int socket_fd,int fd, int number)
{
    int write_bytes, read_bytes;
    char read_buffer[1000], write_buffer[1000];
    memset(read_buffer, 0, sizeof(read_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));

    struct flock unlock_admin;
    unlock_admin.l_type = F_UNLCK;
    unlock_admin.l_whence = SEEK_SET;
    unlock_admin.l_start = number * sizeof(struct Customer);
    unlock_admin.l_len = sizeof(struct Customer);

    int unlocking = fcntl(fd, F_SETLKW, &unlock_admin);

    if (unlocking == -1)
    {
        printf("Error in unlocking the admin");
        exit(0);
    }


}

int lock_Employee1(int socket_fd,int fd, int number) 
{
    int write_bytes, read_bytes;
    char read_buffer[1000], write_buffer[1000];
    memset(read_buffer, 0, sizeof(read_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));

    struct flock Admin_WRITELOCK;
    Admin_WRITELOCK.l_type = F_WRLCK;
    Admin_WRITELOCK.l_whence = SEEK_SET;
    Admin_WRITELOCK.l_start = number * sizeof(struct BankEmployee);
    Admin_WRITELOCK.l_len = sizeof(struct BankEmployee);

    int locking = fcntl(fd, F_SETLKW, &Admin_WRITELOCK);

    if (locking == -1) 
    {
        return 0;
    }
    
    return 1;
}

void unlock_Employee1(int socket_fd,int fd, int number) 
{
    int write_bytes, read_bytes;
    char read_buffer[1000], write_buffer[1000];
    memset(read_buffer, 0, sizeof(read_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));

    struct flock unlock_admin;
    unlock_admin.l_type = F_UNLCK;
    unlock_admin.l_whence = SEEK_SET;
    unlock_admin.l_start = number * sizeof(struct BankEmployee);
    unlock_admin.l_len = sizeof(struct BankEmployee);

    int unlocking = fcntl(fd, F_SETLKW, &unlock_admin);

    if (unlocking == -1)
    {
        printf("Error in unlocking the admin");
        exit(0);
    }


}

int is_acc_Unique(int fd,int a)
{
    struct Customer new_cust[100];
    int b = read(fd,&new_cust,sizeof(new_cust));
    for(int i=0;i<100;i++)
    {   
        if(a == new_cust[i].acc_no)
        return 0;
    }

    // printf("%s",ID);
    return 1;
}

int is_Username_Unique1(int fd,const char *Username)
{
    struct Customer newcust[100];
    int b = read(fd,&newcust,sizeof(newcust));
    for(int i=0;i<100;i++)
    {   
        if(strcmp(Username,newcust[i].username) == 0)
        return 0;
    }

    // printf("%s",ID);
    return 1;
}

void add_customer(int socket_fd)
{

    int write_bytes, read_bytes;
    char read_buffer[1000], write_buffer[1000];
    memset(read_buffer, 0, sizeof(read_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));

    int fd = open("customers.txt",O_CREAT|O_RDWR|O_APPEND,0644);
    if(fd == -1)
    {
        perror("Error opening file");
    }

    // lseek(fd,0,SEEK_END);

    struct Customer new_customer;

    strcpy(write_buffer,"\nEnter New Customer Name :- ");
    write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
    memset(write_buffer, 0, sizeof(write_buffer));
    read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));
    strcpy(new_customer.customer_name,read_buffer);
    memset(read_buffer, 0, sizeof(read_buffer));

    // while(1)
    // {
    //         strcpy(write_buffer,"\nEnter New Customer Account No. :- ");
    //         write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
    //         memset(write_buffer, 0, sizeof(write_buffer));
    //         read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));
    //         int acc = atoi(read_buffer);
    //         memset(read_buffer, 0, sizeof(read_buffer));
    //         if (acc == 0)
    //         {
    //             strcpy(write_buffer, "\n Try something different%");
    //             write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
    //             memset(write_buffer, 0, sizeof(write_buffer));
    //             continue;  
    //         }
    //         // memset(read_buffer, 0, sizeof(read_buffer));
    //         // printf("%d",a);
    //         int a = is_acc_Unique(fd,acc);
    //         if(a == 1)
    //         {
    //             new_customer.acc_no = acc;
    //             break;
    //         }

    //         strcpy(write_buffer,"\n");
    //         strcat(write_buffer,read_buffer);
    //         strcat(write_buffer," Try something different.%");
    //         write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
    //         memset(write_buffer, 0, sizeof(write_buffer));

    // }

    // while(1)
    // {

    //     strcpy(write_buffer,"\nEnter New Employee Role");
    //     strcat(write_buffer,"\nFor Employee Enter 0.");
    //     strcat(write_buffer,"\nFor Mananger Enter 1.");
    //     write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
    //     memset(write_buffer, 0, sizeof(write_buffer));

    //     read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));

    //     if(read_buffer[0] == '0' || read_buffer[0] == '1')
    //     {    
    //         new_employee.role = read_buffer[0];
    //         memset(read_buffer, 0, sizeof(read_buffer));
    //         break;
    //     }
    //     else 
    //     {
    //         memset(read_buffer, 0, sizeof(read_buffer));
    //         strcpy(write_buffer,"\nInvalid role. Please enter 0 or 1.% ");
    //         write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
    //         memset(write_buffer, 0, sizeof(write_buffer));
    //     }

    // }

    while(1)
    {

        strcpy(write_buffer,"\nEnter New Customer Gender :- M or F");
        write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
        memset(write_buffer, 0, sizeof(write_buffer));

        read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));

        if(read_buffer[0] == 'M' || read_buffer[0] == 'F')
        {    
            new_customer.gender = read_buffer[0];
            memset(read_buffer, 0, sizeof(read_buffer));
            break;
        }
        else 
        {
            memset(read_buffer, 0, sizeof(read_buffer));
            strcpy(write_buffer,"\nInvalid Gender. Please enter M or F.% ");
            write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
            memset(write_buffer, 0, sizeof(write_buffer));
        }

    }

    while(1)
    {
            strcpy(write_buffer,"\nEnter New Customer Age :- ");
            write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
            memset(write_buffer, 0, sizeof(write_buffer));
            read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));
            int age = atoi(read_buffer);
            memset(read_buffer, 0, sizeof(read_buffer));
            if(age>0 && age<101)
            {
                new_customer.age = age;
                break;
            }

            strcpy(write_buffer,"\nInput a valid age%");
            write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
            memset(write_buffer, 0, sizeof(write_buffer));

    }


    new_customer.balance = 0;

    while(1)
    {
            strcpy(write_buffer,"\nEnter New Customer username :- ");
            write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
            memset(write_buffer, 0, sizeof(write_buffer));
            read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));

            int a = is_Username_Unique1(fd,read_buffer);
            if(a == 1)
            {
                strcpy(new_customer.username,read_buffer);
                memset(read_buffer, 0, sizeof(read_buffer));
                break;
            }

            strcpy(write_buffer,"\n");
            strcat(write_buffer,read_buffer);
            strcat(write_buffer," Username is already been used. Try something different%");
            write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
            memset(write_buffer, 0, sizeof(write_buffer));

    }

    strcpy(write_buffer,"\nEnter New Customer Password :- ");
    write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
    memset(write_buffer, 0, sizeof(write_buffer));
    read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));
    strcpy(new_customer.password,read_buffer);
    memset(read_buffer, 0, sizeof(read_buffer));

    new_customer.loanID = -1;

    new_customer.last_transaction = -1;

    new_customer.active = false;

    for(int i=0;i<10;i++)
    {
        new_customer.transaction[i] = -1;
    }

    int file_size = lseek(fd, 0, SEEK_END);
    int new_acc_no = (file_size / sizeof(struct Customer)) + 1;
    new_customer.acc_no = new_acc_no;

    write(fd,&new_customer,sizeof(new_customer));

    strcpy(write_buffer,"\n\n New Customer Added Successfully%");
    write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
    memset(write_buffer, 0, sizeof(write_buffer));
        
}

void Modify_Customer_Details1(int socket_fd)
{

    int write_bytes, read_bytes;
    char read_buffer[1000], write_buffer[1000];
    memset(read_buffer, 0, sizeof(read_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));

    int fd = open("customers.txt",O_RDWR);
    if(fd == -1)
    {
        perror("Error opening file");
    }

    struct Customer newcust[100];
    
    int b = read(fd,&newcust,sizeof(newcust));

    while(1)
    {
            strcpy(write_buffer,"\nEnter Customer Account no :- ");
            write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
            memset(write_buffer, 0, sizeof(write_buffer));
            read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));
            int acc = atoi(read_buffer);
            if (acc == 0)
            {
                strcpy(write_buffer, "\nInvalid account number.%");
                write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
                memset(write_buffer, 0, sizeof(write_buffer));
                continue;  
            }
            for(int i=0;i<100;i++)
            {   
                
                if(newcust[i].acc_no == acc)
                {
                    int l = lock_Customer1(socket_fd,fd, i);
                    if(l == 0) 
                    {
                        strcpy(write_buffer,"\nCannot currently modify Customer with Account no. ");
                        strcat(write_buffer,read_buffer);
                        strcat(write_buffer,"%");
                        write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));   
                        return;
                    }
                    memset(read_buffer, 0, sizeof(read_buffer));
                    while(1)
                    {

                        strcpy(write_buffer,"\nThese are customer details \nName of Customer :- ");
                        strcat(write_buffer,newcust[i].customer_name);
                        
                        char temp_buffer[10];  
                        
                        strcat(write_buffer,"\nAge of Customer :- ");
                        sprintf(temp_buffer, "%d", newcust[i].age);  
                        strcat(write_buffer, temp_buffer);

                        temp_buffer[0] = newcust[i].gender;
                        temp_buffer[1] = '\0';  
                        strcat(write_buffer, "\nGender of Customer :- ");
                        strcat(write_buffer, temp_buffer);
                        // strcat(write_buffer, "\n");

                        strcat(write_buffer,"%");
                        write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
                        memset(write_buffer, 0, sizeof(write_buffer));

                        // if(newcust[i].active == true)
                        // {
                        //     strcpy(write_buffer, "Account is currently Active%.");
                        //     write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
                        //     memset(write_buffer, 0, sizeof(write_buffer));
                        // }
                        // else
                        // {
                        //     strcpy(write_buffer, "Account is currently Deactivated%");
                        //     write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
                        //     memset(write_buffer, 0, sizeof(write_buffer));
                        // }
                        

                        strcpy(write_buffer,"\nWhat do you want to Modify :- \n1. Name\n2. Age\n3. Gender\n4. Exit");
                        write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
                        memset(write_buffer, 0, sizeof(write_buffer));
                        read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));
                        int choice = atoi(read_buffer);
                        memset(read_buffer, 0, sizeof(read_buffer));
                        switch (choice)
                        {
                        case 1:
                                strcpy(write_buffer,"\nEnter Name of Customer");
                                write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
                                memset(write_buffer, 0, sizeof(write_buffer));
                                read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));
                                strcpy(newcust[i].customer_name,read_buffer);
                                memset(read_buffer, 0, sizeof(read_buffer));
                                break;
                        case 2:
                                while(1)
                                {
                                        strcpy(write_buffer,"\nEnter Customer Age :- ");
                                        write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
                                        memset(write_buffer, 0, sizeof(write_buffer));
                                        read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));
                                        int age = atoi(read_buffer);
                                        memset(read_buffer, 0, sizeof(read_buffer));
                                        if(age>0 && age<101)
                                        {
                                            newcust[i].age = age;
                                            break;
                                        }

                                        strcpy(write_buffer,"\nInput a valid age%");
                                        write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
                                        memset(write_buffer, 0, sizeof(write_buffer));

                                }
                                
                                break;
                        case 3:
                                while(1)
                                {

                                    strcpy(write_buffer,"\nEnter New Employee Gender :- M or F");
                                    write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
                                    memset(write_buffer, 0, sizeof(write_buffer));

                                    read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));

                                    if(read_buffer[0] == 'M' || read_buffer[0] == 'F')
                                    {    
                                        newcust[i].gender = read_buffer[0];
                                        memset(read_buffer, 0, sizeof(read_buffer));
                                        break;
                                    }
                                    else 
                                    {
                                        memset(read_buffer, 0, sizeof(read_buffer));
                                        strcpy(write_buffer,"\nInvalid Gender. Please enter M or F.% ");
                                        write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
                                        memset(write_buffer, 0, sizeof(write_buffer));
                                    }

                                }
                                break;
                        //  case 4:
                        //         if(newcust[i].active == true)
                        //         {
                        //             strcpy(write_buffer, "\nAccount is currently Active.\nDo you want to deactivate it (y/n)");
                        //             write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
                        //             memset(write_buffer, 0, sizeof(write_buffer));

                        //             read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));
                        //             // Trim newlines or extra characters
                        //             read_buffer[strcspn(read_buffer, "\n")] = 0;

                        //             if(read_buffer[0] == 'y' || read_buffer[0] == 'Y')
                        //             {
                        //                 newcust[i].active = false;
                        //                 lseek(fd, i * sizeof(struct Customer), SEEK_SET);
                        //                 write(fd, &newcust[i], sizeof(struct Customer));
                        //                 strcpy(write_buffer, "\nSuccessfully changed active status of customer account%");
                        //                 write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
                        //                 memset(write_buffer, 0, sizeof(write_buffer));
                        //             }
                        //         }
                        //         else if(newcust[i].active == false)
                        //         {
                        //             strcpy(write_buffer, "\nAccount is currently Deactivated.\nDo you want to activate it (y/n)");
                        //             write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
                        //             memset(write_buffer, 0, sizeof(write_buffer));

                        //             read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));
                        //             // Trim newlines or extra characters
                        //             read_buffer[strcspn(read_buffer, "\n")] = 0;

                        //             if(read_buffer[0] == 'y' || read_buffer[0] == 'Y')
                        //             {
                        //                 newcust[i].active = true;
                        //                 lseek(fd, i * sizeof(struct Customer), SEEK_SET);
                        //                 write(fd, &newcust[i], sizeof(struct Customer));
                        //                 strcpy(write_buffer, "\nSuccessfully changed active status of customer account%");
                        //                 write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
                        //                 memset(write_buffer, 0, sizeof(write_buffer));
                        //             }
                        //         }
            
                        //             break;
                        case 4:
                                lseek(fd, i * sizeof(struct Customer), SEEK_SET);
                                write(fd, &newcust[i], sizeof(struct Customer));
                                unlock_Customer1(socket_fd,fd, i);
                                return;
                        default:
                                strcpy(write_buffer,"\nEnter a Valid choice%");
                                write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
                                memset(write_buffer, 0, sizeof(write_buffer));
                                break;
                        }
                        
                    }
                }
            }

            strcpy(write_buffer,"\nNo Customer with Account no. ");
            strcat(write_buffer,read_buffer);
            strcat(write_buffer,"%");
            write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
            memset(write_buffer, 0, sizeof(write_buffer));
            memset(read_buffer, 0, sizeof(read_buffer));

    }
    
    
}

void changePassword_Employee(int socket_fd,int fd, int number) 
{
    int write_bytes, read_bytes;
    char read_buffer[1000], write_buffer[1000];
    memset(read_buffer, 0, sizeof(read_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));

    struct BankEmployee credentials[100];
    
    lseek(fd, 0, SEEK_SET);  
    int b = read(fd, &credentials, sizeof(credentials));

    if (b == -1) 
    {
        perror("Error reading file");
        return;
    }

    char current_password[15];
    // printf("Enter Current Password: ");
    strcpy(write_buffer,"\nEnter Current Password: ");
    write_bytes = write(socket_fd,write_buffer,sizeof(write_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));
    read_bytes = read(socket_fd,read_buffer,sizeof(read_buffer));
    strcpy(current_password,read_buffer);
    memset(read_buffer, 0, sizeof(read_buffer));

    // fgets(current_password, sizeof(current_password), stdin);
    // current_password[strcspn(current_password, "\n")] = 0;

    if (strcmp(credentials[number].password, current_password) != 0) 
    {
        // printf("Incorrect current password!\n");
        strcpy(write_buffer,"\nIncorrect current password!%");
        write_bytes = write(socket_fd,write_buffer,sizeof(write_buffer));
        memset(write_buffer, 0, sizeof(write_buffer));
        return;
    }

    char new_password[15];
    // printf("Enter new password: ");
    strcpy(write_buffer,"\nEnter new password: ");
    write_bytes = write(socket_fd,write_buffer,sizeof(write_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));
    read_bytes = read(socket_fd,read_buffer,sizeof(read_buffer));
    strcpy(new_password,read_buffer);
    memset(read_buffer, 0, sizeof(read_buffer));
    // fgets(new_password, sizeof(new_password), stdin);
    // new_password[strcspn(new_password, "\n")] = 0;

    strcpy(credentials[number].password, new_password);

    lseek(fd, number * sizeof(struct BankEmployee), SEEK_SET);  
    int write_result = write(fd, &credentials[number], sizeof(struct BankEmployee));

    if (write_result == -1) 
    {
        perror("Error writing to file");
        return;
    }

    
    strcpy(write_buffer,"\nPassword changed successfully%");
    write_bytes = write(socket_fd,write_buffer,sizeof(write_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));
    return;


}

int Checking_login_credentials_Employee(int socket_fd,const char *input_username, const char *input_password, int *number)
{
    int write_bytes, read_bytes;
    char read_buffer[1000], write_buffer[1000];
    memset(read_buffer, 0, sizeof(read_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));

    struct BankEmployee credentials[100];
    
    int fd = open("employees.txt", O_RDWR);
    
    if (fd == -1) 
    {
        perror("Error opening file");
        return 0;
    }

    int b = read(fd, &credentials, sizeof(credentials));

    if (b == -1)
    {
        perror("Error reading file");
        close(fd);
        return 0;
    }

    for (int i = 0; i < 100; i++) 
    {
        if (strcmp(input_username, credentials[i].username) == 0 && strcmp(input_password, credentials[i].password) == 0) 
        {
            if (lock_Employee1(socket_fd,fd, i)) 
            {
                *number = i;
                strcpy(write_buffer,"\nLogin successful! Welcome ");
                strcat(write_buffer,input_username);
                strcat(write_buffer,"%");
                write_bytes = write(socket_fd,write_buffer,sizeof(write_buffer));
                memset(write_buffer, 0, sizeof(write_buffer));
                if(credentials[i].role == '0') return 1;
                if(credentials[i].role == '1') return 2;

            } 
            
            else 
            {
                memset(write_buffer, 0, sizeof(write_buffer));
                strcpy(write_buffer,"\n");
                // strcat(write_buffer,input_username);
                strcat(write_buffer," Cannot currently  in$");
                write_bytes = write(socket_fd,write_buffer,sizeof(write_buffer));    
                memset(write_buffer, 0, sizeof(write_buffer));
                close(fd);
                return 0;
            }
        }
    }

    strcpy(write_buffer,"Invalid User ID or password$");
    write_bytes = write(socket_fd,write_buffer,sizeof(write_buffer));    
    memset(write_buffer, 0, sizeof(write_buffer));
    
    close(fd);
    return 0;
}

void login_employee(int socket_fd) 
{
    int write_bytes, read_bytes;
    char read_buffer[1000], write_buffer[1000];
    memset(read_buffer, 0, sizeof(read_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));

    char username[50];
    char password[50];
    int number = 0;

    strcpy(write_buffer,"\nEnter Username: ");
    write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
    memset(write_buffer, 0, sizeof(write_buffer));
    read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));
    strcpy(username, read_buffer);
    memset(read_buffer, 0, sizeof(read_buffer));

    strcpy(write_buffer, "\nEnter Password: ");
    write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
    memset(write_buffer, 0, sizeof(write_buffer));
    read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));
    strcpy(password, read_buffer);
    memset(read_buffer, 0, sizeof(read_buffer));

    int fd = open("employees.txt", O_RDWR);
    if (fd == -1) 
    {
        perror("Error opening file");
        return;
    }

    int v = Checking_login_credentials_Employee(socket_fd, username, password, &number);

    if (v == 1) 
    {

        while (1) 
        {

            memset(write_buffer, 0, sizeof(write_buffer));
            strcpy(write_buffer, "\n------------Employee Menu------------\n1. Add New Customer\n2. Modify Customer Details\n3. Approve/Reject Loans\n4. View Assigned Loan Applications\n5. Change Password\n6. Logout\n#. Exit\n\nEnter your choice:");
            write_bytes = write(socket_fd,write_buffer,sizeof(write_buffer));
            // write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  // Fix here
            memset(write_buffer, 0, sizeof(write_buffer));

            read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));
            int choice = atoi(read_buffer);
            memset(read_buffer, 0, sizeof(read_buffer));


            switch (choice) 
            {
                case 1:
                    add_customer(socket_fd);
                    break;
                case 2:
                    Modify_Customer_Details1(socket_fd);
                    break;
                case 3:
                    approve_reject_loans(socket_fd,number);
                    break;
                case 4:
                    view_assigned_loans(socket_fd,number);
                    break;
                case 5:
                    changePassword_Employee(socket_fd, fd, number);
                    unlock_Employee1(socket_fd, fd, number);  
                    return;
                case 6:
                    unlock_Employee1(socket_fd, fd, number);  
                    strcpy(write_buffer, "\nEmployee logged out%");
                    write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
                    memset(write_buffer, 0, sizeof(write_buffer));
                    return;
                default:
                    strcpy(write_buffer, "\nInvalid choice! Please try again.%");
                    write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
                    memset(write_buffer, 0, sizeof(write_buffer));
            }
        }
    }
    else if(v == 2) 
    {

        while (1) 
        {

            memset(write_buffer, 0, sizeof(write_buffer));
            strcpy(write_buffer, "\n------------Manager Menu------------\n1. Activate/Deactivate Customers\n2. Assign Loan Application Processes to Employees\n3. Review Customer Feedback\n4. Change Password\n5. Logout\n#. Exit\n\nEnter your choice:");
            write_bytes = write(socket_fd,write_buffer,sizeof(write_buffer));
            // write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  // Fix here
            memset(write_buffer, 0, sizeof(write_buffer));

            read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));
            int choice = atoi(read_buffer);
            memset(read_buffer, 0, sizeof(read_buffer));


            switch (choice) 
            {
                case 1:
                    activate_deactivate_customers(socket_fd);
                    break;
                case 2:
                    assign_loan_applications(socket_fd);
                    break;
                case 3:
                    review_customer_feedback(socket_fd);
                    break;
                case 4:
                    changePassword_Employee(socket_fd, fd, number);
                    unlock_Employee1(socket_fd, fd, number);  
                    return;
                case 5:
                    unlock_Employee1(socket_fd, fd, number);  
                    strcpy(write_buffer, "\nManager logged out%");
                    write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
                    memset(write_buffer, 0, sizeof(write_buffer));
                    return;
                default:
                    strcpy(write_buffer, "\nInvalid choice! Please try again.%");
                    write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
                    memset(write_buffer, 0, sizeof(write_buffer));
            }
        }
    }

    close(fd);
}

#endif