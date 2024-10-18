#ifndef BANK_STRUCTURES_H
#define BANK_STRUCTURES_H

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
    int acc_no;
    float balance;
    bool active;
    int loanID;
    char username[15];
    char password[15];
    int transaction[15];
};

#endif // BANK_STRUCTURES_H
