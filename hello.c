#include <stdio.h>

//returning an integer x as input from user
int test()
{
    int x;
    scanf("%i", &x);
    return x;
}

// void returns none just executes a function
void testprint()
{
    int x = test();
    printf("%i\n", x);
}

//main calls all functions
int main()
{
    testprint();
    return 0;
}