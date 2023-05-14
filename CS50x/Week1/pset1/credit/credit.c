#include <cs50.h>
#include <stdio.h>

// Calculate length of a given number
int get_length(long number)
{
    int i = 0;
    while (number > 0)
    {
        number = number / 10;
        i++;
    }
    return i;
}

// Main function
int main(void)
{
    // Get user's input
    long in_num = get_long("Enter Credit Card's number: ");


    // Verify if user's input is a valid credit card number
    int length = get_length(in_num);

    if (length != 13 && length != 15 && length != 16)
    {
        printf("INVALID\n");
        return 0;
    }


    int total_sum1 = 0;
    int total_sum2 = 0;
    int total = 0;
    long n = in_num;
    int modulus1;
    int modulus2;
    int d1;
    int d2;
    long firsts = n;

    do
    {
        // Extract every second digit and add them together
        modulus1 = n % 10;
        n = n / 10;
        total_sum1 = total_sum1 + modulus1;

        // Extract every odd placed digit
        modulus2 = n % 10;
        n = n / 10;

        // Multiply by 2 every second last digit and add the results together
        modulus2 = modulus2 * 2;
        d1 = modulus2 % 10;
        d2 = modulus2 / 10;
        total_sum2 = total_sum2 + d1 + d2;
    }
    while (n > 0);

    // Sum of products ann digits that weren't multiplied
    total = total_sum1 + total_sum2;

    // Check if modulo 10 does not equals 0 and prints "INVALID"
    if (total % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

// Identify Card Issuer

    // Get first 2 to digits
    do
    {
        firsts = firsts / 10;
    }
    while (firsts > 100);

    // Print out Card Issuer's Name accordingly

    // MASTERCARD
    if ((firsts / 10 == 5) && (firsts % 10 > 0 && firsts % 10 < 6))
    {
        printf("MASTERCARD\n");
    }

    // AMERICAN EXPRESS
    else if ((firsts / 10 == 3) && (firsts % 10 == 4 || firsts % 10 == 7))
    {
        printf("AMEX\n");
    }

    // VISA
    else if (firsts / 10 == 4)
    {
        printf("VISA\n");
    }

    else
    {
        printf("INVALID\n");
    }

}