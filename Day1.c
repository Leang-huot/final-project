#include <stdio.h>
#include <string.h>
#define Limit_User 100
//Day 1 
typedef struct {
    char username[50];
    int password;
}User_login;
typedef struct{

    char Acc_name[50];
    double USD;
    double KHR;

    double savingUSD;
    double savingKHR;

    User_login;
}account;


AccountCreation();
AccountLogin;


void interface(){
    int choice;
    
    printf("----------WELCOME TO OUR BANK----------\n");

    printf("1.Create account\n");
    printf("Login into account\n");
    printf("3.Log out from account\n");
    printf("---------------------------------------\n");
    printf("Enter your choice :");
    scanf("%d", &choice);

    do{
        switch(choice){
            case 1: 
                AccountCreation();

                break;
            case 2:
                AccountLogin();
                break;
            case 3: 
                printf("Thanks You For using our service\n");
                break;
                printf("Choice is Invalid,Please try again");
        }
    }while ( choice != 3);

}
int main(){
    interface();
    
    return 0;
}