#include <stdio.h>
#include <string.h>
#include <ctype.h>
//Day 1 
//Structure
typedef struct {
  
    char username[50];
    char password[20];
}User_login;
typedef struct{
    char Acc_name[50];
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


int LoginFunction();
void interface();
void AccountCreation();
void BankingFunction(int index);
void CheckBalance(int index);
void DepositFunction(int index);

int main(){
    interface();

    return 0;
}
//Interface
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
            case 2:{
                int index = LoginFunction();

                if (index != -1) {
                    printf("\nLogin successful!\n");
                    BankingFunction(index);
                } else {
                    printf("\nInvalid username or password.\n");
                }
                break;
            }
            case 3: 
                printf("----------THANK YOU FORR USING OUR APP----------\n");
                break;
        default :
            printf("Invalid choice. Try again\n");
        }
    }while ( choice != 3);

}
//Create account funtion
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
        scanf("%49s", NewAccount.Acc_name);
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
    printf("Account Username: %s\n", NewAccount.Acc_name);
    printf("Accont logint name : %s\n", NewAccount.login.username);
    printf("Account ID: %d\n", NewAccount.accountNumber);
    
}
// Login funtion
int LoginFunction(){
    char Log_User[50];
    char Log_Pass[50];
    if (accountcount == 0) {
        printf("There's no account to login\n");
        return -1;
    }


    printf("-----Login into your account-----\n");
    printf("Enter Your Username to login :");
    scanf("%49s", Log_User);
    printf("Enter Your Password to login :");
    scanf("%19s", Log_Pass);
//i < accountcount mean on login with one account 
/*Return i mean send back the index of that account
account[0]
account[1]
*/
    for (int i = 0; i<accountcount;i++){
        if(strcmp(Log_User , Accounts[i].login.username) == 0 &&
           strcmp(Log_Pass , Accounts[i].login.password) == 0){

            return i;
           }     
    }
//Return -1 = there no account to log, so log is impossible
    return -1;

}

//Funtion For Banking
//parameter index mean which accounts in account[] currently in 
void BankingFunction(int index){
    int choice = 0;
    do{

        printf("------BANKING MENU------\n");
        printf("Welcome Bong %s\n" , Accounts[index].Acc_name);
        printf("Account ID: %d\n",  Accounts[index].accountNumber);
        printf("------------------------\n");

        printf("1.Check balance\n");
        printf("2.deposit money\n");
        printf("3.Transfer money\n");
        printf("4.Withdraw money\n");
        printf("5.Log out\n");

        printf("Enter your choice : ");
        scanf("%d" , &choice);

        switch(choice){
            case 1:
                CheckBalance(index);
                break;
            case 2:
                DepositFunction(index);
                break;
            case 3 :
                break;
            case 4 :
                break;
            case 5 :
                printf("Log out successfully \n");
        }


    }while(choice !=5);
}

void CheckBalance(int index){
    printf("Your Current USD Balance is : %.2lf\n", Accounts[index].USD);
    printf("Your Current Balance is : %.2lf\n", Accounts[index].KHR);
    printf("Your Saving USD Balance is : %.2lf\n" , Accounts[index].savingUSD);
    printf("Your Saving KHR balance is  : %.2lf\n" , Accounts[index].savingKHR);
    
}

void DepositFunction(int index){
    int currencyChoice;
    double amount;


    printf("\n----------Deposit Money----------\n");
    printf("1.Deposit USD\n");
    printf("2.Deposit KHR\n");
    printf("Enter your choice: ");
    scanf("%d", &currencyChoice);

    printf("Enter USD amount : ");
    scanf("%lf" , &amount);
    if (amount <= 0){
        printf("You must deposit more than 0\n");
        return;
    }
    if (currencyChoice == 1){
        Accounts[index].USD += amount;
        printf("Deposit successfuly\n");
        printf("Your current balance now is : %.2lf USD\n",Accounts[index].USD);
    }
    else if (currencyChoice == 2){
        Accounts[index].KHR += amount*4100;
        printf("Deposit successfuly\n");
        printf("Your current balance now is : %.2lf KHR\n",Accounts[index].KHR);
    }

    else{
        printf("Invalid Choice\n");
    }
}