# Author: Eskabore
# Purpose: calculating minimum number of coins required to give a user change
# Language: Python

# Import the get_float function from the cs50 library
from cs50 import get_float

# Define a function to calculate the change


def get_dollars():
    # Keep prompting user until a non-negative value is entered
    while True:
        number = get_float("Enter number of dollars: ")
        if number >= 0:
            break
    return number

# Define a function to calculate the minimum number of quarters required


def calculate_quarters(cents):
    # Divide the number of cents by the value of a quarter (25 cents)
    # and return the integer quotient
    dividend, divisor = cents, 25
    quotient = dividend // divisor
    return quotient

# Define a function to calculate the minimum number of dimes required


def calculate_dimes(cents):
    # Divide the number of cents by the value of a dime (10 cents)
    # and return the integer quotient
    dividend, divisor = cents, 10
    quotient = dividend // divisor
    return quotient

# Define a function to calculate the minimum number of nickels required


def calculate_nickels(cents):
    # Divide the number of cents by the value of a nickel (5 cents)
    # and return the integer quotient
    dividend, divisor = cents, 5
    quotient = dividend // divisor
    return quotient

# Define a function to calculate the minimum number of pennies required


def calculate_pennies(cents):
    # Divide the number of cents by the value of a penny (1 cents)
    # and return the integer quotient
    dividend, divisor = cents, 1
    quotient = dividend // divisor
    return quotient

# Define the main function


def main():
    # Get the amount owed from the user
    dollars = get_dollars()
    # Convert the amount to cents
    cents = int(dollars * 100)
    # Calculate the minimum number of quarters required
    quarters = calculate_quarters(cents)
    # Substract the value of the quarters from the total number of cents
    cents -= quarters * 25
    # Calculate the minimum number of dimes required
    dimes = calculate_dimes(cents)
    # Substract the value of the dimes from the total number of cents
    cents -= dimes * 10
    # Calculate the minimum number of nickels required
    nickels = calculate_nickels(cents)
    # Substract the value of the nickels from the total number of cents
    cents -= nickels * 5
    # Calculate the minimum number of quarters required
    pennies = calculate_pennies(cents)
    # Calculate and print total number of coins
    # owed from the user
    coins = quarters + dimes + nickels + pennies
    print("{}".format(coins))


# Call main function
if __name__ == "__main__":
    main()