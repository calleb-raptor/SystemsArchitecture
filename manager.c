#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <stdlib.h>

struct Account
{
    char name[256];
    int accountNumber;
};

struct Transaction
{
    int id;
    int accountID;
    double amount;
    char narrative[256];
    char date[256];
};

void newAccount();
int exitManu();
int accountList();
void invalidInput();
void accountNumberFlow(struct Account account);
int initialiseDB();
int saveAccount(struct Account account);
int callback();
int callcount();
int viewTrans();
void newTrans(struct Transaction transaction);
int saveTrans(struct Transaction transaction);

void invalidInput()
{
    printf("Invalid input...\n");
}

void menu()
{
    printf("Hello!\nPlease select one of the following options by typing the number and enter:\n1. New Account\n2. List Accounts\n3. View Transactions\n4. Exit\n");
    int option;
    // scanf("%i", &option);
    scanf("%i", &option);
    switch (option)
    {
    case 1:
        newAccount();
        break;
    case 2:
        accountList();
        break;
    case 3:
        viewTrans();
        break;
    case 4:
        exitManu();
        break;
    default:
        invalidInput();
    }
}

int viewTrans()
{
    int accountNumber;
    struct Transaction transaction;
    sqlite3 *db;
    char *err_msg = 0;
    int rc = sqlite3_open("BankManager.db", &db);
    char option;
    if (rc != SQLITE_OK)
    {
        printf("Error opening database\n");
        sqlite3_close(db);
        return 1;
    }
    printf("Please choose an account to view by inputting the account number:\n");
    scanf(" %i", &accountNumber);
    printf("getting transactions...\n");

    char *sql = sqlite3_mprintf("SELECT * FROM transactions WHERE accountID = %i", accountNumber);

    char *count = sqlite3_mprintf("SELECT count(accountID) FROM transactions WHERE accountID = %i", accountNumber);

    rc = sqlite3_exec(db, count, callcount, 0, &err_msg);

    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);

    if (rc != SQLITE_OK)
    {
        printf("Error opening database: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_close(db);

    printf("Would you like to add a new transaction to the database?\n");

    scanf(" %c", &option);

    switch (option)
    {
    case 'y':
    case 'Y':
        transaction.accountID = accountNumber;
        newTrans(transaction);
        break;
    case 'n':
    case 'N':
        exitManu();
        break;
    default:
        invalidInput();
    }
    return 0;
}

int callcount(void *NotUsed, int argc, char **argv, char **azColName)
{
    NotUsed = 0;
    for (int i = 0; i < argc; ++i)
    {
        printf("You have %s transactions:\n", argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void newTrans(struct Transaction transaction)
{
    char ack;
    printf("New transaction\nPlease input the amount of the transaction:\n");
    scanf(" %lf", &transaction.amount);
    printf("Enter Narrative:\n");
    scanf(" %s", transaction.narrative);
    printf("Enter date of transaction\n");
    scanf(" %s", transaction.date);
    printf("You have entered the below transaction details:\nAmount: %f\nNarrative: %s\nDate: %s\n", transaction.amount, transaction.narrative, transaction.date);
    transaction.id = 1;
    printf("Are these details correct?\n");
    printf("[Y]    [N]\n");
    scanf(" %c", &ack);
    switch (ack)
    {
    case 'y':
    case 'Y':
        saveTrans(transaction);
        printf("Saving...\n");
        break;
    case 'n':
    case 'N':
        exitManu();
        break;
    default:
        invalidInput();
    }
}

int saveTrans(struct Transaction transaction)
{
    sqlite3 *db;
    char *err_msg = 0;
    int rc = sqlite3_open("BankManager.db", &db);
    if (rc != SQLITE_OK)
    {
        printf("Error opening database\n");
        sqlite3_close(db);
        return 1;
    }

    printf("transaction: %s\namount: %f\n", transaction.narrative, transaction.amount);

    char *sql = sqlite3_mprintf("INSERT INTO transactions(accountID, amount, narrative, date) VALUES(%i, %f, '%s', '%s');", transaction.accountID, transaction.amount, transaction.narrative, transaction.date);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK)
    {
        printf("Error opening database: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_close(db);
    return 0;
}

int exitManu()
{
    printf("Exiting...");
    return 0;
}

int accountList()
{
    sqlite3 *db;
    char *err_msg = 0;
    char ack;
    int rc = sqlite3_open("BankManager.db", &db);

    if (rc != SQLITE_OK)
    {
        printf("Error opening database\n");
        sqlite3_close(db);
        return 1;
    }

    char *sql = "SELECT * FROM accounts;";
    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);

    if (rc != SQLITE_OK)
    {
        printf("Error opening database: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_close(db);
    printf("Would you like to view transactions within an account?\nPlease choose an account to view:\n");
    printf("[Y]    [N]\n");
    scanf(" %c", &ack);
    switch (ack)
    {
    case 'y':
    case 'Y':
        viewTrans();
        break;
    case 'n':
    case 'N':
        exitManu();
        break;
    default:
        invalidInput();
    }
    return 0;
}

int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    NotUsed = 0;
    for (int i = 0; i < argc; ++i)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void newAccount()
{
    char name[20];
    char agreement;
    struct Account account;
    printf("New Account!\nPlease enter the name of the account:\n");
    scanf("%s", name);
    printf("You entered: %s\nIs this correct?\n", name);
    printf("[Y]    [N]\n");
    scanf(" %c", &agreement);
    switch (agreement)
    {
    case 'y':
    case 'Y':
        strcpy(account.name, name);
        accountNumberFlow(account);
        break;
    case 'n':
    case 'N':
        exitManu();
        break;
    default:
        invalidInput();
    }
}

void accountNumberFlow(struct Account account)
{
    int accountNumber;
    char agreement;
    printf("Great, now please enter your account number:\n");
    scanf(" %i", &accountNumber);
    printf("You entered: %i\nIs this correct?\n", accountNumber);
    printf("[Y]      [N]\n");
    scanf(" %c", &agreement);

    switch (agreement)
    {
    case 'y':
    case 'Y':
        account.accountNumber = accountNumber;
        printf("Account set up with below details:\nAccount Name: %s\nAccount Number: %i\n", account.name, account.accountNumber);
        saveAccount(account);
        break;
    case 'n':
    case 'N':
        printf("Okay... Would you like to change the details of the account?\nPlease restart the program...");
        break;
    default:
        invalidInput();
    }
}

int saveAccount(struct Account account)
{
    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("BankManager.db", &db);

    if (rc != SQLITE_OK)
    {
        printf("Error opening database\n");
        sqlite3_close(db);
        return 1;
    }

    char *sql = sqlite3_mprintf("INSERT INTO accounts(name, number) VALUES('%s', %i)", account.name, account.accountNumber);
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK)
    {
        printf("Error opening database: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_close(db);
    return 0;
}

int initialiseDB()
{
    char *err_msg = 0;
    sqlite3 *db;
    int rc = sqlite3_open("BankManager.db", &db);

    if (rc != SQLITE_OK)
    {
        printf("Error opening database\n");
        sqlite3_close(db);
        return 1;
    }

    char *sql = "CREATE TABLE IF NOT EXISTS accounts(name TEXT, number INT);"
                "CREATE TABLE IF NOT EXISTS transactions(accountID INT, Amount TEXT, Narrative TEXT, Date TEXT)";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK)
    {
        printf("Error opening database\n");
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_close(db);
    return 0;
}

int main()
{
    initialiseDB();
    menu();
    return 0;
}