#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Define
#define Limit_User 100
#define Max_History 100
#define EXCHANGE_RATE 4100.0
#define INTEREST_RATE 0.05   // 5% per year

// Structure
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

int LoginAccount();
void AccountMenu(int index);

void CheckBalance(int index);
void DepositMoney(int index);
void WithdrawMoney(int index);

void TransferMoney(int index);
int FindAccountByNumber(int accountNumber);

// Saving functions
void SavingMenu(int index);
void MoveToSaving(int index);
void WithdrawFromSaving(int index);
void ApplyInterest(int index);

// Transaction history functions
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

        int passwordLength = strlen(NewAccount.login.password);

        if (passwordLength != 6) {
            valid = 0;
        }

        for (int i = 0; i < passwordLength; i++) {
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
        printf("5. Saving Account\n");
        printf("6. Transaction History\n");
        printf("7. Logout\n");
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
                SavingMenu(index);
                break;

            case 6:
                ShowTransactionHistory(index);
                break;

            case 7:
                printf("\nLogout successful.\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 7);
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
    char description[150];

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
    int transferChoice;
    double amount;
    double convertedAmount;

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

    printf("\nChoose transfer type:\n");
    printf("1. USD to USD\n");
    printf("2. KHR to KHR\n");
    printf("3. USD to KHR\n");
    printf("4. KHR to USD\n");
    printf("Enter your choice: ");
    scanf("%d", &transferChoice);

    printf("Enter amount: ");
    scanf("%lf", &amount);

    if (amount <= 0) {
        printf("\nAmount must be greater than 0.\n");
        return;
    }

    switch (transferChoice) {
        case 1:
            if (amount <= Accounts[index].USD) {
                Accounts[index].USD -= amount;
                Accounts[receiverIndex].USD += amount;

                sprintf(senderDescription, "Transferred %.2lf USD to account %d",
                        amount, Accounts[receiverIndex].accountNumber);

                sprintf(receiverDescription, "Received %.2lf USD from account %d",
                        amount, Accounts[index].accountNumber);

                AddTransaction(index, senderDescription);
                AddTransaction(receiverIndex, receiverDescription);

                printf("\nTransfer successful!\n");
                printf("You transferred %.2lf USD to %s.\n", amount, Accounts[receiverIndex].login.Acc_name);
                printf("Your new USD balance: %.2lf USD\n", Accounts[index].USD);
            } else {
                printf("\nNot enough USD balance.\n");
            }
            break;

        case 2:
            if (amount <= Accounts[index].KHR) {
                Accounts[index].KHR -= amount;
                Accounts[receiverIndex].KHR += amount;

                sprintf(senderDescription, "Transferred %.2lf KHR to account %d",
                        amount, Accounts[receiverIndex].accountNumber);

                sprintf(receiverDescription, "Received %.2lf KHR from account %d",
                        amount, Accounts[index].accountNumber);

                AddTransaction(index, senderDescription);
                AddTransaction(receiverIndex, receiverDescription);

                printf("\nTransfer successful!\n");
                printf("You transferred %.2lf KHR to %s.\n", amount, Accounts[receiverIndex].login.Acc_name);
                printf("Your new KHR balance: %.2lf KHR\n", Accounts[index].KHR);
            } else {
                printf("\nNot enough KHR balance.\n");
            }
            break;

        case 3:
            if (amount <= Accounts[index].USD) {
                convertedAmount = amount * EXCHANGE_RATE;

                Accounts[index].USD -= amount;
                Accounts[receiverIndex].KHR += convertedAmount;

                sprintf(senderDescription, "Transferred %.2lf USD to account %d as %.2lf KHR",
                        amount, Accounts[receiverIndex].accountNumber, convertedAmount);

                sprintf(receiverDescription, "Received %.2lf KHR from account %d converted from %.2lf USD",
                        convertedAmount, Accounts[index].accountNumber, amount);

                AddTransaction(index, senderDescription);
                AddTransaction(receiverIndex, receiverDescription);

                printf("\nTransfer successful!\n");
                printf("You transferred %.2lf USD.\n", amount);
                printf("Receiver received %.2lf KHR.\n", convertedAmount);
                printf("Exchange rate: 1 USD = %.0lf KHR\n", EXCHANGE_RATE);
                printf("Your new USD balance: %.2lf USD\n", Accounts[index].USD);
            } else {
                printf("\nNot enough USD balance.\n");
            }
            break;

        case 4:
            if (amount <= Accounts[index].KHR) {
                convertedAmount = amount / EXCHANGE_RATE;

                Accounts[index].KHR -= amount;
                Accounts[receiverIndex].USD += convertedAmount;

                sprintf(senderDescription, "Transferred %.2lf KHR to account %d as %.2lf USD",
                        amount, Accounts[receiverIndex].accountNumber, convertedAmount);

                sprintf(receiverDescription, "Received %.2lf USD from account %d converted from %.2lf KHR",
                        convertedAmount, Accounts[index].accountNumber, amount);

                AddTransaction(index, senderDescription);
                AddTransaction(receiverIndex, receiverDescription);

                printf("\nTransfer successful!\n");
                printf("You transferred %.2lf KHR.\n", amount);
                printf("Receiver received %.2lf USD.\n", convertedAmount);
                printf("Exchange rate: 1 USD = %.0lf KHR\n", EXCHANGE_RATE);
                printf("Your new KHR balance: %.2lf KHR\n", Accounts[index].KHR);
            } else {
                printf("\nNot enough KHR balance.\n");
            }
            break;

        default:
            printf("\nInvalid transfer choice.\n");
    }
}

// Saving menu
void SavingMenu(int index) {
    int choice = 0;

    do {
        printf("\n----------SAVING ACCOUNT MENU----------\n");
        printf("1. Move money to saving\n");
        printf("2. Withdraw money from saving\n");
        printf("3. Apply interest\n");
        printf("4. Back to account menu\n");
        printf("---------------------------------------\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                MoveToSaving(index);
                break;

            case 2:
                WithdrawFromSaving(index);
                break;

            case 3:
                ApplyInterest(index);
                break;

            case 4:
                printf("\nBack to account menu.\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 4);
}

// Move money from normal balance to saving balance
void MoveToSaving(int index) {
    int currencyChoice;
    double amount;
    char description[150];

    printf("\n----------MOVE MONEY TO SAVING----------\n");
    printf("1. Move USD to Saving USD\n");
    printf("2. Move KHR to Saving KHR\n");
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
            Accounts[index].savingUSD += amount;

            sprintf(description, "Moved %.2lf USD to Saving USD", amount);
            AddTransaction(index, description);

            printf("\nMoved to saving successfully!\n");
            printf("Current USD Balance: %.2lf USD\n", Accounts[index].USD);
            printf("Saving USD Balance: %.2lf USD\n", Accounts[index].savingUSD);
        } else {
            printf("Not enough USD balance.\n");
        }
    }
    else if (currencyChoice == 2) {
        if (amount <= Accounts[index].KHR) {
            Accounts[index].KHR -= amount;
            Accounts[index].savingKHR += amount;

            sprintf(description, "Moved %.2lf KHR to Saving KHR", amount);
            AddTransaction(index, description);

            printf("\nMoved to saving successfully!\n");
            printf("Current KHR Balance: %.2lf KHR\n", Accounts[index].KHR);
            printf("Saving KHR Balance: %.2lf KHR\n", Accounts[index].savingKHR);
        } else {
            printf("Not enough KHR balance.\n");
        }
    }
    else {
        printf("Invalid currency choice.\n");
    }
}

// Withdraw money from saving back to normal balance
void WithdrawFromSaving(int index) {
    int currencyChoice;
    double amount;
    char description[150];

    printf("\n----------WITHDRAW FROM SAVING----------\n");
    printf("1. Withdraw from Saving USD\n");
    printf("2. Withdraw from Saving KHR\n");
    printf("Enter your choice: ");
    scanf("%d", &currencyChoice);

    printf("Enter amount: ");
    scanf("%lf", &amount);

    if (amount <= 0) {
        printf("Amount must be greater than 0.\n");
        return;
    }

    if (currencyChoice == 1) {
        if (amount <= Accounts[index].savingUSD) {
            Accounts[index].savingUSD -= amount;
            Accounts[index].USD += amount;

            sprintf(description, "Withdrew %.2lf USD from Saving USD", amount);
            AddTransaction(index, description);

            printf("\nWithdraw from saving successful!\n");
            printf("Current USD Balance: %.2lf USD\n", Accounts[index].USD);
            printf("Saving USD Balance: %.2lf USD\n", Accounts[index].savingUSD);
        } else {
            printf("Not enough Saving USD balance.\n");
        }
    }
    else if (currencyChoice == 2) {
        if (amount <= Accounts[index].savingKHR) {
            Accounts[index].savingKHR -= amount;
            Accounts[index].KHR += amount;

            sprintf(description, "Withdrew %.2lf KHR from Saving KHR", amount);
            AddTransaction(index, description);

            printf("\nWithdraw from saving successful!\n");
            printf("Current KHR Balance: %.2lf KHR\n", Accounts[index].KHR);
            printf("Saving KHR Balance: %.2lf KHR\n", Accounts[index].savingKHR);
        } else {
            printf("Not enough Saving KHR balance.\n");
        }
    }
    else {
        printf("Invalid currency choice.\n");
    }
}

// Apply interest to saving account
void ApplyInterest(int index) {
    int currencyChoice;
    int months;
    double interest;
    char description[150];

    printf("\n----------APPLY SAVING INTEREST----------\n");
    printf("Interest rate: %.2lf%% per year\n", INTEREST_RATE * 100);

    printf("1. Apply interest to Saving USD\n");
    printf("2. Apply interest to Saving KHR\n");
    printf("Enter your choice: ");
    scanf("%d", &currencyChoice);

    printf("Enter number of months: ");
    scanf("%d", &months);

    if (months <= 0) {
        printf("Months must be greater than 0.\n");
        return;
    }

    if (currencyChoice == 1) {
        if (Accounts[index].savingUSD <= 0) {
            printf("You do not have money in Saving USD.\n");
            return;
        }

        interest = Accounts[index].savingUSD * INTEREST_RATE * months / 12;
        Accounts[index].savingUSD += interest;

        sprintf(description, "Applied interest for %d months: earned %.2lf USD", months, interest);
        AddTransaction(index, description);

        printf("\nInterest added successfully!\n");
        printf("Interest earned: %.2lf USD\n", interest);
        printf("New Saving USD Balance: %.2lf USD\n", Accounts[index].savingUSD);
    }
    else if (currencyChoice == 2) {
        if (Accounts[index].savingKHR <= 0) {
            printf("You do not have money in Saving KHR.\n");
            return;
        }

        interest = Accounts[index].savingKHR * INTEREST_RATE * months / 12;
        Accounts[index].savingKHR += interest;

        sprintf(description, "Applied interest for %d months: earned %.2lf KHR", months, interest);
        AddTransaction(index, description);

        printf("\nInterest added successfully!\n");
        printf("Interest earned: %.2lf KHR\n", interest);
        printf("New Saving KHR Balance: %.2lf KHR\n", Accounts[index].savingKHR);
    }
    else {
        printf("Invalid choice.\n");
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