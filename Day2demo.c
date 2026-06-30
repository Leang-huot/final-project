#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Day 1
// Structure
#define Limit_User 100
#define Max_History 100

typedef struct {
    char description[150];
} Transaction;

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

    Transaction history[Max_History];
    int historyCount;

} account;

// Global Variable
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
void WithdrawMoney(int index);
void TransferMoney(int index);
int FindAccountByNumber(int accountNumber);

// Day 3 function prototype
void AddTransaction(int index, char description[]);
void ShowTransactionHistory(int index);

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
    NewAccount.historyCount = 0;

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
        printf("5. Transaction History\n");
        printf("6. Logout\n");
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
                WithdrawMoney(index);
                break;

            case 4:
                TransferMoney(index);
                break;

            case 5:
                ShowTransactionHistory(index);
                break;

            case 6:
                printf("\nLogout successful.\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 6);
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
    char description[150];

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

        sprintf(description, "Deposited %.2lf USD", amount);
        AddTransaction(index, description);

        printf("\nDeposit successful!\n");
        printf("New USD Balance: %.2lf USD\n", Accounts[index].USD);
    } 
    else if (currencyChoice == 2) {
        Accounts[index].KHR += amount;

        sprintf(description, "Deposited %.2lf KHR", amount);
        AddTransaction(index, description);

        printf("\nDeposit successful!\n");
        printf("New KHR Balance: %.2lf KHR\n", Accounts[index].KHR);
    } 
    else {
        printf("Invalid currency choice.\n");
    }
}

// Withdraw money function
void WithdrawMoney(int index) {
    int currencyChoice;
    double amount;
    char description[100];

    printf("\n----------WITHDRAW MONEY----------\n");
    printf("1. Withdraw USD\n");
    printf("2. Withdraw KHR\n");
    printf("Enter your choice: ");
    scanf("%d", &currencyChoice);

    printf("Enter amount: ");
    scanf("%lf", &amount);

    if (amount <= 0) {
        printf("Amount must be greater than 0.\n");
        return;
    }

    if (currencyChoice == 1) {
        if (amount <= Accounts[index].USD) {
            Accounts[index].USD -= amount;

            sprintf(description, "Withdrew %.2lf USD", amount);
            AddTransaction(index, description);

            printf("\nWithdraw successful!\n");
            printf("New USD Balance: %.2lf USD\n", Accounts[index].USD);
        } else {
            printf("Not enough USD balance.\n");
        }
    } 
    else if (currencyChoice == 2) {
        if (amount <= Accounts[index].KHR) {
            Accounts[index].KHR -= amount;

            sprintf(description, "Withdrew %.2lf KHR", amount);
            AddTransaction(index, description);

            printf("\nWithdraw successful!\n");
            printf("New KHR Balance: %.2lf KHR\n", Accounts[index].KHR);
        } else {
            printf("Not enough KHR balance.\n");
        }
    } 
    else {
        printf("Invalid currency choice.\n");
    }
}

// Find account by account number
int FindAccountByNumber(int accountNumber) {
    for (int i = 0; i < accountcount; i++) {
        if (Accounts[i].accountNumber == accountNumber) {
            return i;
        }
    }

    return -1;
}

// Transfer money function
void TransferMoney(int index) {
    int receiverAccountNumber;
    int receiverIndex;
    int currencyChoice;
    double amount;

    char senderDescription[150];
    char receiverDescription[150];

    printf("\n----------TRANSFER MONEY----------\n");

    printf("Enter receiver Account ID: ");
    scanf("%d", &receiverAccountNumber);

    receiverIndex = FindAccountByNumber(receiverAccountNumber);

    if (receiverIndex == -1) {
        printf("\nReceiver account not found.\n");
        return;
    }

    if (receiverIndex == index) {
        printf("\nYou cannot transfer money to your own account.\n");
        return;
    }

    printf("\nReceiver name: %s\n", Accounts[receiverIndex].login.Acc_name);
    printf("Receiver Account ID: %d\n", Accounts[receiverIndex].accountNumber);

    printf("\nChoose currency to transfer:\n");
    printf("1. Transfer USD\n");
    printf("2. Transfer KHR\n");
    printf("Enter your choice: ");
    scanf("%d", &currencyChoice);

    printf("Enter amount: ");
    scanf("%lf", &amount);

    if (amount <= 0) {
        printf("\nAmount must be greater than 0.\n");
        return;
    }

    if (currencyChoice == 1) {
        if (amount <= Accounts[index].USD) {
            Accounts[index].USD -= amount;
            Accounts[receiverIndex].USD += amount;

            sprintf(senderDescription, "Transferred %.2lf USD to account %d", amount, Accounts[receiverIndex].accountNumber);
            sprintf(receiverDescription, "Received %.2lf USD from account %d", amount, Accounts[index].accountNumber);

            AddTransaction(index, senderDescription);
            AddTransaction(receiverIndex, receiverDescription);

            printf("\nTransfer successful!\n");
            printf("You transferred %.2lf USD to %s.\n", amount, Accounts[receiverIndex].login.Acc_name);
            printf("Your new USD balance: %.2lf USD\n", Accounts[index].USD);
        } else {
            printf("\nNot enough USD balance.\n");
        }
    } 
    else if (currencyChoice == 2) {
        if (amount <= Accounts[index].KHR) {
            Accounts[index].KHR -= amount;
            Accounts[receiverIndex].KHR += amount;

            sprintf(senderDescription, "Transferred %.2lf KHR to account %d", amount, Accounts[receiverIndex].accountNumber);
            sprintf(receiverDescription, "Received %.2lf KHR from account %d", amount, Accounts[index].accountNumber);

            AddTransaction(index, senderDescription);
            AddTransaction(receiverIndex, receiverDescription);

            printf("\nTransfer successful!\n");
            printf("You transferred %.2lf KHR to %s.\n", amount, Accounts[receiverIndex].login.Acc_name);
            printf("Your new KHR balance: %.2lf KHR\n", Accounts[index].KHR);
        } else {
            printf("\nNot enough KHR balance.\n");
        }
    } 
    else {
        printf("\nInvalid currency choice.\n");
    }
}

// Add transaction history
void AddTransaction(int index, char description[]) {
    if (Accounts[index].historyCount >= Max_History) {
        printf("\nTransaction history is full.\n");
        return;
    }

    strcpy(Accounts[index].history[Accounts[index].historyCount].description, description);
    Accounts[index].historyCount++;
}

// Show transaction history
void ShowTransactionHistory(int index) {
    printf("\n----------TRANSACTION HISTORY----------\n");

    if (Accounts[index].historyCount == 0) {
        printf("No transaction history yet.\n");
        return;
    }

    for (int i = 0; i < Accounts[index].historyCount; i++) {
        printf("%d. %s\n", i + 1, Accounts[index].history[i].description);
    }
}