#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

struct Account
{
    char name[256];
    int accountNumber;
};

void newAccount();
int exitManu();
void accountList();
void invalidInput();
void accountNumberFlow(struct Account account);
int initialiseDB();
int saveAccount();

void invalidInput()
{
    printf("Invalid input...\n");
}

void menu()
{
    printf("Hello!\nPlease select one of the following options by typing the number and enter:\n1. New Account\n2. List Accounts\n3. Exit\n");
    int option;
    // scanf("%i", &option);

    switch (scanf("%i", &option))
    {
    case 1:
        newAccount();
        break;
    case 2:
        accountList();
        break;
    case 3:
        exitManu();
        break;
    default:
        invalidInput();
    }
}

int exitManu()
{
    printf("Exiting...");
    return 0;
}

void accountList()
{
    printf("This is where the account list will go");
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
        // TODO: Insert new account details into database
        break;
    case 'n':
    case 'N':
        printf("Okay... Would you like to change the details of the account?\nPlease restart the program...");
        break;
    default:
        invalidInput();
    }
}

int saveAccount()
{
    // TODO: Implement :: how to insert scoped variables from a struct Account?
    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("BankManager.db", &db);

    if (rc != SQLITE_OK)
    {
        printf("Error opening database\n");
        sqlite3_close(db);
        return 1;
    }

    char *sql = "INSERT INTO accounts VALUES(?,?,?)";
    return 0;
}

int initialiseDB()
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

    char *sql = "CREATE TABLE IF NOT EXISTS accounts(id, name, number);";

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