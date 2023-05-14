#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    int number;

    // Get user input
    do
    {
        number = get_int("Enter number of cents: ");
    }
    while (number < 0);
    return number;
}

int calculate_quarters(int cents)
{
    int dividend, divisor, quotient;
    dividend = cents;
    divisor = 25;
    quotient = dividend / divisor;

    // Displays the amount of quarters, alert the user if none are required
    if (quotient > 0)
    {
        printf("Quarters = %i\n", quotient);
    }
    else
    {
        printf("No quarter\n");
    }
    return quotient;
}

int calculate_dimes(int cents)
{
    int dividend, divisor, quotient;
    dividend = cents;
    divisor = 10;
    quotient = dividend / divisor;

    // Displays the amount of dimes, alert the user if none are required
    if (quotient > 0)
    {
        printf("Dimes = %i\n", quotient);
    }
    else
    {
        printf("No dime\n");
    }
    return quotient;
}

int calculate_nickels(int cents)
{
    int dividend, divisor, quotient;
    dividend = cents;
    divisor = 5;
    quotient = dividend / divisor;

    // Displays the amount of nickels, alert the user if none are required
    if (quotient > 0)
    {
        printf("Nickels = %i\n", quotient);
    }
    else
    {
        printf("No Nickels\n");
    }
    return quotient;
}

int calculate_pennies(int cents)
{
    int dividend, divisor, quotient;
    dividend = cents;
    divisor = 1;
    quotient = dividend / divisor;

    // Displays the amount of pennies, alert the user if none are required
    if (quotient > 0)
    {
        printf("Pennies = %i\n", quotient);
    }
    else
    {
        printf("No pennies\n");
    }
    return quotient;
}
