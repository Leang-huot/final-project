#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Day 1
// Structure
typedef struct {
    char Acc_name[50];
    char username[50];
    char password[20];
} User_login;

typedef struct {
    int accountNumber;
    double USD;
    double KHR;

    double savingUSD;
    double savingKHR;

    User_login login;
} account;

// Global Variable
#define Limit_User 100

account Accounts[Limit_User];
int accountcount = 0;
int NextAccountNumber = 100;

// Function prototype
void interface();
void AccountCreation();

// Day 2 function prototype
int LoginAccount();
void AccountMenu(int index);
void CheckBalance(int index);
void DepositMoney(int index);


int main() {
    interface();

    return 0;
}

// Interface
void interface() {
    int choice = 0;

    do {
        printf("\n----------WELCOME TO OUR BANK----------\n");
        printf("1. Create account\n");
        printf("2. Login into account\n");
        printf("3. Exit the app\n");
        printf("---------------------------------------\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                AccountCreation();
                break;

            case 2: {
                int index = LoginAccount();

                if (index != -1) {
                    printf("\nLogin successful!\n");
                    AccountMenu(index);
                } else {
                    printf("\nInvalid username or password.\n");
                }

                break;
            }

            case 3:
                printf("----------THANK YOU FOR USING OUR APP----------\n");
                break;

            default:
                printf("Invalid choice. Try again\n");
        }

    } while (choice != 3);
}

// Create account function
void AccountCreation() {
    int valid;
    account NewAccount;

    if (accountcount >= Limit_User) {
        printf("Full user access. You cannot create account anymore\n");
        return;
    }

    NewAccount.accountNumber = NextAccountNumber;
    NextAccountNumber++;

    printf("\n------Please Create Your Account To Login------\n");

    printf("Enter Account name: ");
    scanf(" %49[^\n]", NewAccount.login.Acc_name);

    printf("Enter your username: ");
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
            printf("Password must enter 6 numbers only. Please try again.\n");
        }

    } while (valid == 0);

    NewAccount.USD = 0;
    NewAccount.KHR = 0;
    NewAccount.savingUSD = 0;
    NewAccount.savingKHR = 0;

    Accounts[accountcount] = NewAccount;
    accountcount++;

    printf("\n------Account created successfully!------\n");
    printf("Account name: %s\n", NewAccount.login.Acc_name);
    printf("Account login name: %s\n", NewAccount.login.username);
    printf("Account ID: %d\n", NewAccount.accountNumber);
}

// Login account function
int LoginAccount() {
    char inputUsername[50];
    char inputPassword[20];

    if (accountcount == 0) {
        printf("\nNo account has been created yet.\n");
        return -1;
    }

    printf("\n----------LOGIN ACCOUNT----------\n");

    printf("Enter username: ");
    scanf("%49s", inputUsername);

    printf("Enter password: ");
    scanf("%19s", inputPassword);

    for (int i = 0; i < accountcount; i++) {
        if (strcmp(inputUsername, Accounts[i].login.username) == 0 &&
            strcmp(inputPassword, Accounts[i].login.password) == 0) {

            return i;
        }
    }

    return -1;
}

// Account menu after login
void AccountMenu(int index) {
    int choice = 0;

    do {
        printf("\n----------ACCOUNT MENU----------\n");
        printf("Welcome, %s\n", Accounts[index].login.Acc_name);
        printf("Account ID: %d\n", Accounts[index].accountNumber);
        printf("--------------------------------\n");
        printf("1. Check Balance\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Transfer Money\n");
        printf("5. Logout\n");
        printf("--------------------------------\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                CheckBalance(index);
                break;

            case 2:
                DepositMoney(index);
                break;

            case 3:
          
                break;

            case 4:
              
                break;

            case 5:
                printf("\nLogout successful.\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 5);
}

// Check balance function
void CheckBalance(int index) {
    printf("\n----------BALANCE----------\n");
    printf("USD Balance: %.2lf USD\n", Accounts[index].USD);
    printf("KHR Balance: %.2lf KHR\n", Accounts[index].KHR);
    printf("Saving USD: %.2lf USD\n", Accounts[index].savingUSD);
    printf("Saving KHR: %.2lf KHR\n", Accounts[index].savingKHR);
}

// Deposit money function
void DepositMoney(int index) {
    int currencyChoice;
    double amount;

    printf("\n----------DEPOSIT MONEY----------\n");
    printf("1. Deposit USD\n");
    printf("2. Deposit KHR\n");
    printf("Enter your choice: ");
    scanf("%d", &currencyChoice);

    printf("Enter amount: ");
    scanf("%lf", &amount);

    if (amount <= 0) {
        printf("Amount must be greater than 0.\n");
        return;
    }

    if (currencyChoice == 1) {
        Accounts[index].USD += amount;
        printf("\nDeposit successful!\n");
        printf("New USD Balance: %.2lf USD\n", Accounts[index].USD);
    } 
    else if (currencyChoice == 2) {
        Accounts[index].KHR += amount;
        printf("\nDeposit successful!\n");
        printf("New KHR Balance: %.2lf KHR\n", Accounts[index].KHR);
    } 
    else {
        printf("Invalid currency choice.\n");
    }
}

