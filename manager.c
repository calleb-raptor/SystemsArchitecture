#include <stdio.h>
#include <string.h>

void newAccount();

void menu()
{
    printf("Hello!\nPlease select one of the following options by typing the number and enter:\n1. New Account\n2. List Accounts\n3. Exit\n");
    int option;
    scanf("%i", &option);

    if (option == 1)
    {
        newAccount();
    }
}

void newAccount()
{
    char name[20];
    char agreement;
    printf("New Account!\nPlease enter the name of the account:\n");
    scanf("%s", name);
    printf("You entered: %s\nIs this correct?\n", name);
    printf("[Y]      [N]\n");
    scanf("%c", agreement);
    if (agreement == 'Y')
    {
        int accountNumber;
        printf("Great, now please enter your account number:\n");
        scanf("%i", &accountNumber);
        printf("You entered: %i\nIs this correct?\n", accountNumber);
        printf("[Y]      [N]\n");
        scanf("%c", agreement);
    }
}

int main()
{
    menu();
    return 0;
}