#include <stdio.h>
#include <string.h>
#include <ctype.h>
//Day 1 
//Structure
typedef struct {
    char Acc_name[50];
    char username[50];
    char password[20];
}User_login;
typedef struct{
    int accountNumber;
    double USD;
    double KHR;

    double savingUSD;
    double savingKHR;

    User_login login;
}account;
//Global Variable
#define Limit_User 100
account Accounts[Limit_User];
int accountNumber;
int accountcount = 0;
int NextAccountNumber = 100;

void interface();
void AccountCreation();

int main(){
    interface();

    return 0;
}
void interface(){
    int choice = 0;
    

    do{
    printf("\n----------WELCOME TO OUR BANK----------\n");
    printf("1.Create account\n");
    printf("2.Login into account\n");
    printf("3.Exit the app\n");
    printf("---------------------------------------\n");
   
    printf("Enter your choice :");
        scanf("%d", &choice);
        switch(choice){
            case 1: 
                AccountCreation();

                break;
            case 2:
                printf("not create yet");
                break;
            case 3: 
                printf("----------THANK YOU FORR USING OUR APP----------\n");
                break;
        default :
            printf("Invalid choice. Try again\n");
        }
    }while ( choice != 3);

}

void AccountCreation(){
    int valid;
    account NewAccount;
    NewAccount.accountNumber = NextAccountNumber;
    NextAccountNumber++;
    if(accountcount >= Limit_User){
        printf("Full user access. You cannot create account anymore\n");
        return;
    }
    printf("------Please Create Your Account To Login------\n");
    printf("Enter Account name : ");
        scanf("%49s", NewAccount.login.Acc_name);
    printf("Enter your username :");
        scanf("%49s", NewAccount.login.username);
do {
    valid = 1;

    printf("Enter Your Password: ");
    scanf("%19s", NewAccount.login.password);

    if (strlen(NewAccount.login.password) != 6) {
        valid = 0;
    }

    for (int i = 0; i < strlen(NewAccount.login.password); i++) {
        if (!isdigit(NewAccount.login.password[i])) {
            valid = 0;
        }
    }

    if (valid == 0) {
        printf("Password must enter 6 number only.Please try again.\n");
    }

}while (valid == 0);
    NewAccount.USD = 0;
    NewAccount.KHR = 0;
    NewAccount.savingUSD = 0;
    NewAccount.savingKHR = 0;

    Accounts[accountcount] = NewAccount;
    accountcount++;
    printf("\n------Account created successfully------!\n");
    printf("Account Username: %s\n", NewAccount.login.Acc_name);
    printf("Accont logint name : %s\n", NewAccount.login.username);
    printf("Account ID: %d\n", NewAccount.accountNumber);
    
}