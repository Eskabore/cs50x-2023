# Author
# Purpose: Program determines whether a provided credit card number is valid according to Luhn's algorithm
# Language: Python

from cs50 import get_int, get_string


def get_length(number):
    # Calculate length of a given number
    i = 0
    while number > 0:
        number = number // 10
        i += 1
    return i


def main():
    # Get user's input
    in_num = get_int("Enter Credit Card's number: ")

    # Verify if user's input is a valid credit card number
    length = get_length(in_num)
    if length != 13 and length != 15 and length != 16:
        print("INVALID")
        return

    total_sum1 = 0
    total_sum2 = 0
    total = 0
    n = in_num
    firsts = n
    while n > 0:
        # Extract every second digit and add them together
        modulus1 = n % 10
        n = n // 10
        total_sum1 += modulus1

        # Extract every odd placed digit
        modulus2 = n % 10
        n = n // 10

        # Multiply by 2 every second last digit and add the results together
        modulus2 = modulus2 * 2
        d1 = modulus2 % 10
        d2 = modulus2 // 10
        total_sum2 += d1 + d2

    # Sum of products and digits that weren't multiplied
    total = total_sum1 + total_sum2

    # Check if modulo 10 does not equals 0 and prints "INVALID"
    if total % 10 != 0:
        print("INVALID")
        return

    # Identify Card Issuer

    while firsts > 100:
        firsts = firsts // 10

    # Print out Card's Name accordingly

    # Mastercard
    if firsts // 10 == 5 and firsts % 10 > 0 and firsts % 10 < 6:
        print("MASTERCARD")
    # AMERICAN EXPRESS
    elif firsts // 10 == 3 and firsts % 10 in (4, 7):
        print("AMEX")
    # VISA
    elif firsts // 10 == 4:
        print("VISA")
    else:
        print("INVALID")


main()