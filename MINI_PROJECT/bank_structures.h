#ifndef BANK_STRUCTURES_H
#define BANK_STRUCTURES_H
#include <stdbool.h>
#include<time.h>


struct LoginCredentials 
{
    char username[15];
    char password[15];
};

struct BankEmployee 
{
    char employee_name[50];
    char id[15];
    char role;
    int total_loans;
    char gender;
    int age;
    char username[15];
    char password[15];
    int loan[10];
};

struct Customer
{
    char customer_name[50];
    int acc_no;
    char gender;
    int age;
    float balance;
    bool active;
    int loanID;
    char username[15];
    char password[15];
    int transaction[15];
};


struct Loan
{
    int loanId;
    float amount;
    int customer_acc_no;
    char employee_ID[15];
    int loanStatus; // 0 - not assigned to employee // 1 - assigned to employee // -1 - rejected // 2 - accepted
};

struct Feedback
{
    int id;
    char feed_back[100];
    bool review;
};

struct Transaction 
{
    int transaction_id;
    int customer_account_no;
    float amount;
    int transaction_type; // 1 Deposit // 2 Withdraw // 3 Loan // 4 Transfer Money - Sender's end // 5 Transfer Money - Receiver's end 
    time_t transaction_time;
};

#endif // BANK_STRUCTURES_H
 