#ifndef BANK_STRUCTURES_H
#define BANK_STRUCTURES_H
#include <stdbool.h>

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

struct Feedback
{
    int id;
    char feed_back[100];
    bool review;
};

#endif // BANK_STRUCTURES_H
