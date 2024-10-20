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

    int locking = fcntl(fd, F_SETLK, &Admin_WRITELOCK);

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

    int unlocking = fcntl(fd, F_SETLK, &unlock_admin);

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

    int locking = fcntl(fd, F_SETLK, &Admin_WRITELOCK);

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

    int unlocking = fcntl(fd, F_SETLK, &unlock_admin);

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

    while(1)
    {
            strcpy(write_buffer,"\nEnter New Customer Account No. :- ");
            write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
            memset(write_buffer, 0, sizeof(write_buffer));
            read_bytes = read(socket_fd, read_buffer, sizeof(read_buffer));
            int acc = atoi(read_buffer);
            memset(read_buffer, 0, sizeof(read_buffer));
            if (acc == 0)
            {
                strcpy(write_buffer, "\n Try something different%");
                write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
                memset(write_buffer, 0, sizeof(write_buffer));
                continue;  
            }
            // memset(read_buffer, 0, sizeof(read_buffer));
            // printf("%d",a);
            int a = is_acc_Unique(fd,acc);
            if(a == 1)
            {
                new_customer.acc_no = acc;
                break;
            }

            strcpy(write_buffer,"\n");
            strcat(write_buffer,read_buffer);
            strcat(write_buffer," Try something different.%");
            write_bytes = write(socket_fd, write_buffer, sizeof(write_buffer));  
            memset(write_buffer, 0, sizeof(write_buffer));

    }

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

    new_customer.active = false;

    for(int i=0;i<10;i++)
    {
        new_customer.transaction[i] = -1;
    }

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
                        strcpy(write_buffer,"\nCannot currently modify Employee ");
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
                strcat(write_buffer,input_username);
                strcat(write_buffer," is already logged in$");
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
            strcpy(write_buffer, "\n------------Employee Menu------------\n1. Add New Customer\n2. Modify Customer Details\n3. Process Loan Applications\n4. Approve/Reject Loans\n5. View Assigned Loan Applications\n6. Change Password\n7. Logout\n\nEnter your choice:");
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
                    // process_loan_applications(socket_fd);
                    break;
                case 4:
                    // approve_reject_loans(socket_fd);
                    break;
                case 5:
                    // view_assigned_loans(socket_fd);
                    break;
                case 6:
                    changePassword_Employee(socket_fd, fd, number);
                    unlock_Employee1(socket_fd, fd, number);  // 
                    return;
                case 7:
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
            strcpy(write_buffer, "\n------------Manager Menu------------\n1. Activate/Deactivate Customers\n2. Assign Loan Application Processes to Employees\n3. Review Customer Feedback\n4. Change Password\n5. Logout\n\nEnter your choice:");
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
                    // assign_loan_applications(socket_fd);
                    break;
                case 3:
                    // review_customer_feedback(socket_fd);
                    break;
                case 4:
                    changePassword_Employee(socket_fd, fd, number);
                    unlock_Employee1(socket_fd, fd, number);  // Assuming this is for unlocking employee
                    return;
                case 5:
                    unlock_Employee1(socket_fd, fd, number);  // Logout and unlock employee
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