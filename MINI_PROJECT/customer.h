#ifndef CUSTOMER
#define CUSTOMER

#include "common1.h"
#include "bank_structures.h"


void Apply_For_Loan(int socket_fd,int number)
{
    int write_bytes, read_bytes;
    char read_buffer[1000], write_buffer[1000];
    memset(read_buffer, 0, sizeof(read_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));

    struct Customer credentials[100];

    int fd = open("customers.txt",O_RDWR);
    
    lseek(fd, 0, SEEK_SET);  
    int b = read(fd, &credentials, sizeof(credentials));

    if (b == -1) 
    {
        perror("Error reading file");
        return;
    }

    int fd1 = open("loan.txt",O_CREAT|O_RDWR,0644);
    if(fd1 == -1)
    {
        perror("Erron opening file");
    }

    if(credentials[number].loanID == -1)
    {
        while(1)
        {

            strcpy(write_buffer,"\nEnter Amount of money you would like to loan");
            write_bytes = write(socket_fd,write_buffer,sizeof(write_buffer));
            memset(write_buffer, 0, sizeof(write_buffer));
            read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));
            float loan_amt = atof(read_buffer);
            memset(read_buffer, 0, sizeof(read_buffer));
            if(loan_amt <= 0)
            {
                strcpy(write_buffer, "\n Enter a no. greater than 0%");
                write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
                memset(write_buffer, 0, sizeof(write_buffer));
                continue;  
            }
            if(loan_amt > 1000000)
            {
                strcpy(write_buffer, "\n Enter a no. less than 10,00,000%");
                write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
                memset(write_buffer, 0, sizeof(write_buffer));
                continue;  
            }
            
            credentials[number].loanID = 0;

            struct Loan l;
            l.amount = loan_amt;
            l.customer_acc_no = credentials[number].acc_no;
            strcpy(l.employee_ID, "not assigned");
            l.loanStatus = 0;
            l.loanId = (lseek(fd1,0,SEEK_END)/sizeof(struct Loan)) + 1 ;

            credentials[number].loanID = l.loanId;

            lseek(fd, number * sizeof(struct Customer), SEEK_SET);
            write(fd,&credentials[number],sizeof(struct Customer));

            write(fd1, &l, sizeof(struct Loan));

            strcpy(write_buffer,"\nYour loan request has been sent. Please wait a few days.%");
            write_bytes = write(socket_fd,write_buffer,sizeof(write_buffer));
            memset(write_buffer, 0, sizeof(write_buffer));
            return;
        }
        
    }
    else
    {
        strcpy(write_buffer,"\nYou currently cannot apply for a loan.%");
        write_bytes = write(socket_fd,write_buffer,sizeof(write_buffer));
        memset(write_buffer, 0, sizeof(write_buffer));
        return;
    }

    return;
}

void Add_Feedback(int socket_fd)
{
    int fd = open("feedback.txt",O_CREAT|O_RDWR,0644);
    if(fd == -1)
    {
        perror("Error Opening File");
        return;
    }

    int write_bytes, read_bytes;
    char read_buffer[1000], write_buffer[1000];
    memset(read_buffer, 0, sizeof(read_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));

    int file_size = lseek(fd,0,SEEK_END);

    struct Feedback feed;
    feed.id = (file_size/sizeof(struct Feedback))+1;

    feed.review = false;

    strcpy(write_buffer,"\nWrite Your Feedback. And after completing press Enter");
    write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
    memset(write_buffer, 0, sizeof(write_buffer));
    read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));
    strcpy(feed.feed_back, read_buffer);
    memset(read_buffer, 0, sizeof(read_buffer));

    lseek(fd, 0, SEEK_END);  
    write_bytes = write(fd, &feed, sizeof(feed));  
    if (write_bytes == -1)
    {
        perror("Error Writing Feedback to File");
        close(fd);
        return;
    }

    strcpy(write_buffer,"\nYour Feedback is been Recorded%");
    write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
    memset(write_buffer, 0, sizeof(write_buffer));

}

void Transfer_Money(int socket_fd,int number)
{
    int write_bytes, read_bytes;
    char read_buffer[1000], write_buffer[1000];
    memset(read_buffer, 0, sizeof(read_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));

    struct Customer credentials[100];

    int fd = open("customers.txt", O_RDWR);
    
    lseek(fd, 0, SEEK_SET);  
    int b = read(fd, &credentials, sizeof(credentials));

    if (b == -1) 
    {
        perror("Error reading file");
        return;
    }

    int a = credentials[number].acc_no;

    char temp_buffer[50];

    while (1)
    {

        strcpy(write_buffer, "\nCurrent Account balance :- ");
        sprintf(temp_buffer, "%.2f", credentials[number].balance);
        strcat(write_buffer, temp_buffer);
        strcat(write_buffer, "%");
        write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
        memset(write_buffer, 0, sizeof(write_buffer));

        float c = credentials[number].balance;

        if (c <= 0.00001)
        {
            strcpy(write_buffer, "\nNo money in Account to Send%");
            write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
            memset(write_buffer, 0, sizeof(write_buffer));
            close(fd);
            return;
        }


        
        while(1)
        {
            strcpy(write_buffer, "\nEnter Account No of person you would like to send money");
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
            if (acc == a)
            {
                strcpy(write_buffer, "\nCannot send money to yourself.%");
                write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
                memset(write_buffer, 0, sizeof(write_buffer));
                continue;  
            }
            for(int i=0;i<100;i++)
            {   
                
                if(credentials[i].acc_no == acc)
                {
                    int l = lock_Customer1(socket_fd,fd, i);
                    if(l == 0) 
                    {
                        strcpy(write_buffer,"\nCannot currently Send Money to Customer with Account no. ");
                        strcat(write_buffer,read_buffer);
                        strcat(write_buffer,"%");
                        write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));   
                        return;
                    }
                    memset(read_buffer, 0, sizeof(read_buffer));
                    while(1)
                    {

                        strcpy(write_buffer,"\nThese are details of the Account you want to send money\nName of Customer :- ");
                        strcat(write_buffer,credentials[i].customer_name);
                        
                        char temp_buffer[10];  
                        
                        strcat(write_buffer,"\nAge of Customer :- ");
                        sprintf(temp_buffer, "%d", credentials[i].age);  
                        strcat(write_buffer, temp_buffer);

                        temp_buffer[0] = credentials[i].gender;
                        temp_buffer[1] = '\0';  
                        strcat(write_buffer, "\nGender of Customer :- ");
                        strcat(write_buffer, temp_buffer);

                        strcat(write_buffer,"%");
                        write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
                        memset(write_buffer, 0, sizeof(write_buffer));
                        
                        strcpy(write_buffer, "\nEnter Amount of money you would like to send");
                        write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
                        memset(write_buffer, 0, sizeof(write_buffer));

                        read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));
                        float money_withdrawed = atof(read_buffer);
                        memset(read_buffer, 0, sizeof(read_buffer));

                        if (money_withdrawed <= 0)
                        {
                            strcpy(write_buffer, "\nEnter a number greater than 0%");
                            write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
                            memset(write_buffer, 0, sizeof(write_buffer));
                            continue;  
                        }
                        else if (money_withdrawed > c)
                        {
                            strcpy(write_buffer, "\nInsufficient Balance in Account. Enter a number less than Current Account Balance%");
                            write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
                            memset(write_buffer, 0, sizeof(write_buffer));
                            continue;  
                        }

                        credentials[number].balance -= money_withdrawed;
                        lseek(fd, number * sizeof(struct Customer), SEEK_SET);
                        write(fd, &credentials[number], sizeof(struct Customer));

                        credentials[i].balance += money_withdrawed;
                        lseek(fd, i * sizeof(struct Customer), SEEK_SET);
                        write(fd, &credentials[i], sizeof(struct Customer));

                        strcpy(write_buffer, "\nAccount balance after sending money :- ");
                        sprintf(temp_buffer, "%.2f", credentials[number].balance);
                        strcat(write_buffer, temp_buffer);
                        strcat(write_buffer, "%");
                        write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
                        memset(write_buffer, 0, sizeof(write_buffer));

                        close(fd);
                        return;
                        
                        
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
}

void View_Account_Balance(int socket_fd,int number)
{
    int write_bytes, read_bytes;
    char read_buffer[1000], write_buffer[1000];
    memset(read_buffer, 0, sizeof(read_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));

    struct Customer credentials[100];

    int fd = open("customers.txt",O_RDONLY);
    
    lseek(fd, 0, SEEK_SET);  
    int b = read(fd, &credentials, sizeof(credentials));

    if (b == -1) 
    {
        perror("Error reading file");
        return;
    }
    char temp_buffer[50];
    strcpy(write_buffer,"\nAccount balance :- ");
    sprintf(temp_buffer, "%.2f", credentials[number].balance);
    strcat(write_buffer, temp_buffer);
    strcat(write_buffer,"%");
    write_bytes = write(socket_fd,write_buffer,sizeof(write_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));
    return;
}

void Deposit_Money(int socket_fd,int number)
{
    int write_bytes, read_bytes;
    char read_buffer[1000], write_buffer[1000];
    memset(read_buffer, 0, sizeof(read_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));

    struct Customer credentials[100];

    int fd = open("customers.txt",O_RDWR);
    
    lseek(fd, 0, SEEK_SET);  
    int b = read(fd, &credentials, sizeof(credentials));

    if (b == -1) 
    {
        perror("Error reading file");
        return;
    }
    char temp_buffer[50];
    
    strcpy(write_buffer,"\nAccount balance :- ");
    sprintf(temp_buffer, "%.2f", credentials[number].balance);
    strcat(write_buffer, temp_buffer);
    strcat(write_buffer,"%");
    write_bytes = write(socket_fd,write_buffer,sizeof(write_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));


    while(1)
    {
        strcpy(write_buffer,"\nEnter Amount of money you would like to deposit");
        write_bytes = write(socket_fd,write_buffer,sizeof(write_buffer));
        memset(write_buffer, 0, sizeof(write_buffer));
        read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));
        float money_deposited = atof(read_buffer);
        memset(read_buffer, 0, sizeof(read_buffer));
        if(money_deposited <= 0)
                {
                    strcpy(write_buffer, "\n Enter a no. greater than 0%");
                    write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
                    memset(write_buffer, 0, sizeof(write_buffer));
                    continue;  
                }
        
        credentials[number].balance += money_deposited;
        lseek(fd, number * sizeof(struct Customer), SEEK_SET);
        write(fd, &credentials[number], sizeof(struct Customer));
        char temp_buffer[50];
        strcpy(write_buffer,"\nAccount balance after depositing :- ");
        sprintf(temp_buffer, "%.2f", credentials[number].balance);
        strcat(write_buffer, temp_buffer);
        strcat(write_buffer,"%");
        write_bytes = write(socket_fd,write_buffer,sizeof(write_buffer));
        memset(write_buffer, 0, sizeof(write_buffer));
        return;
    }

    

    return;
}

void Withdraw_Money(int socket_fd, int number)
{
    int write_bytes, read_bytes;
    char read_buffer[1000], write_buffer[1000];
    memset(read_buffer, 0, sizeof(read_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));

    struct Customer credentials[100];

    int fd = open("customers.txt", O_RDWR);
    
    lseek(fd, 0, SEEK_SET);  
    int b = read(fd, &credentials, sizeof(credentials));

    if (b == -1) 
    {
        perror("Error reading file");
        return;
    }

    char temp_buffer[50];
    strcpy(write_buffer, "\nCurrent Account balance :- ");
    sprintf(temp_buffer, "%.2f", credentials[number].balance);
    strcat(write_buffer, temp_buffer);
    strcat(write_buffer, "%");
    write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));

    float c = credentials[number].balance;

    if (c <= 0.00001)
    {
        strcpy(write_buffer, "\nNo money in Account to withdraw%");
        write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
        memset(write_buffer, 0, sizeof(write_buffer));
        close(fd);
        return;
    }

    while (1)
    {
        strcpy(write_buffer, "\nEnter Amount of money you would like to withdraw");
        write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
        memset(write_buffer, 0, sizeof(write_buffer));

        read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));
        float money_withdrawed = atof(read_buffer);
        memset(read_buffer, 0, sizeof(read_buffer));

        if (money_withdrawed <= 0)
        {
            strcpy(write_buffer, "\nEnter a number greater than 0%");
            write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
            memset(write_buffer, 0, sizeof(write_buffer));
            continue;  
        }
        else if (money_withdrawed > c)
        {
            strcpy(write_buffer, "\nInsufficient Balance in Account. Enter a number less than Current Account Balance%");
            write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
            memset(write_buffer, 0, sizeof(write_buffer));
            continue;  
        }

        credentials[number].balance -= money_withdrawed;
        lseek(fd, number * sizeof(struct Customer), SEEK_SET);
        write(fd, &credentials[number], sizeof(struct Customer));

        strcpy(write_buffer, "\nAccount balance after withdrawing :- ");
        sprintf(temp_buffer, "%.2f", credentials[number].balance);
        strcat(write_buffer, temp_buffer);
        strcat(write_buffer, "%");
        write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));
        memset(write_buffer, 0, sizeof(write_buffer));

        close(fd);
        return;
    }
}

int lock_Customer2(int socket_fd,int fd, int number) 
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

void unlock_Customer2(int socket_fd,int fd, int number)
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

void changePassword_customer(int socket_fd,int fd, int number) 
{
    int write_bytes, read_bytes;
    char read_buffer[1000], write_buffer[1000];
    memset(read_buffer, 0, sizeof(read_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));

    struct Customer credentials[100];
    
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

int Checking_login_credentials2(int socket_fd,const char *input_username, const char *input_password, int *number) 
{
    int write_bytes, read_bytes;
    char read_buffer[1000], write_buffer[1000];
    memset(read_buffer, 0, sizeof(read_buffer));
    memset(write_buffer, 0, sizeof(write_buffer));

    struct Customer credentials[100];
    
    int fd = open("customers.txt", O_RDWR);
    
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
            if (lock_Customer2(socket_fd,fd, i)) 
            {
                if(credentials[i].active == true)
                {
                    *number = i;
                    strcpy(write_buffer,"\nLogin successful! Welcome ");
                    strcat(write_buffer,input_username);
                    strcat(write_buffer,"%");
                    write_bytes = write(socket_fd,write_buffer,sizeof(write_buffer));
                    memset(write_buffer, 0, sizeof(write_buffer));
                    return 1;
                }
                else
                {
                    strcpy(write_buffer,"\n");
                    strcat(write_buffer,input_username);
                    strcat(write_buffer," account is deactivated");
                    strcat(write_buffer,"%");
                    write_bytes = write(socket_fd,write_buffer,sizeof(write_buffer));
                    memset(write_buffer, 0, sizeof(write_buffer));
                    unlock_Customer2(socket_fd, fd, i);
                    return 0;
                }
            } 
            
            else 
            {
                memset(write_buffer, 0, sizeof(write_buffer));
                strcpy(write_buffer,"\n");
                strcat(write_buffer,input_username);
                strcat(write_buffer," Cannot currently log in$");
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

void login_customer(int socket_fd) 
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

    int fd = open("customers.txt", O_RDWR);
    if (fd == -1) 
    {
        perror("Error opening file");
        return;
    }

    int v = Checking_login_credentials2(socket_fd, username, password, &number);

    if (v) 
    {

        while (1) 
        {
            memset(write_buffer, 0, sizeof(write_buffer));
            strcpy(write_buffer, "\n------------Customer Menu------------\n1. View Account Balance\n2. Deposit Money\n3. Withdraw Money\n4. Transfer Funds\n5. Apply for a Loan\n6. Change Password\n7. Add Feedback\n8. View Transaction History\n9. Logout\n\nEnter your choice:");
            write_bytes = write(socket_fd,write_buffer,sizeof(write_buffer));
            // write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
            memset(write_buffer, 0, sizeof(write_buffer));

            read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));
            int choice = atoi(read_buffer);
            memset(read_buffer, 0, sizeof(read_buffer));


            switch (choice) 
            {
                case 1:
                        View_Account_Balance(socket_fd,number);
                    break;
                case 2:
                        Deposit_Money(socket_fd,number);
                    break;
                case 3:
                        Withdraw_Money(socket_fd,number);
                    break;
                case 4:
                        Transfer_Money(socket_fd,number);
                    break;
                case 5:
                        Apply_For_Loan(socket_fd,number);
                    break;
                case 6:
                        changePassword_customer(socket_fd, fd, number);
                        unlock_Customer2(socket_fd, fd, number);
                    return;
                case 7:
                        Add_Feedback(socket_fd);
                    break;
                case 8:
                    // View_Transaction_History(socket_fd);
                    break;
                case 9:
                        unlock_Customer2(socket_fd, fd, number);
                        strcpy(write_buffer, "\nCustomer logged out%");
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