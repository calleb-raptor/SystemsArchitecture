#include <stdio.h>

void newAccount();
int exitManu();
void accountList();

void menu()
{
    printf("Hello!\nPlease select one of the following options by typing the number and enter:\n1. New Account\n2. List Accounts\n3. Exit\n");
    int option;
    scanf("%i", &option);

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
    printf("New Account!\nPlease enter the name of the account:\n");
    scanf(" %s", name);
    printf("You entered: %s\nIs this correct?\n", name);
    printf("[Y]    [N]\n");
    scanf(" %c", &agreement);
    if (agreement == 'Y')
    {
        int accountNumber;
        // char ack;
        printf("Great, now please enter your account number:\n");
        scanf(" %i", &accountNumber);
        printf("You entered: %i\nIs this correct?\n", accountNumber);
        printf("[Y]      [N]\n");
        scanf(" %c", &agreement);
        // change this to a swich case
        if (agreement == 'Y')
        {
            printf("Account set up with below details:\nAccount Name: %s\nAccount Number: %i\n", name, accountNumber);
        }
        else if (agreement == 'N')
        {
            printf("Okay... Would you like to change the details of the account?\nPlease restart the program...");
        }
        else
        {
            printf("Invalid input...");
        }
    }
    else if (agreement == 'N')
    {
        printf("Exiting...");
    }
    // create a function in and of itself for invalid input...makes the code more reusable
    else
    {
        printf("Invalid input...");
    }
}

int main()
{
    menu();
    return 0;
}