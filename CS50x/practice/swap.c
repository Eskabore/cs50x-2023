// The following code tends to demonstrate the difference between heap & stack memory
#include <stdio.h>

void swap(int a, int b);
void realswap( int *a, int *b);

int main (void)
{
    int x = 1;
    int y = 2;

    printf("x is %p, y is %p\n", &x, &y);
    printf("x is %i, y is %i\n", x, y);
    realswap(&x, &y);
    printf("x is %p, y is %p\n", &x, &y);
    printf("x is %i, y is %i\n", x, y);
}

void swap(int a, int b)
{
    printf("a is %i, b is %i\n", a, b);
    int tmp = a;
    a = b;
    b = tmp;
    printf("a is %i, b is %i\n", a, b);
}

void realswap( int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}