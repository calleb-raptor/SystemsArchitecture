#include <stdio.h>

int test()
{
    int x;
    scanf("%i", &x);
    return x;
}

void testprint()
{
    int x = test();
    printf("%i\n", x);
}

int main()
{
    testprint();
    return 0;
}