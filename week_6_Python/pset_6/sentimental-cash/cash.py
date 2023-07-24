# TODO
from cs50 import get_float


def main():
    # Ask how many cents the customer is owed
    cents = get_cents()

    # Calculate the number of quarters to give the customer
    quarters = calculate_quarters(cents)
    cents = cents - quarters * 25

    # Calculate the number of dimes to give the customer
    dimes = calculate_dimes(cents)
    cents = cents - dimes * 10

    # Calculate the number of nickels to give the customer
    nickels = calculate_nickels(cents)
    cents = cents - nickels * 5

    # Calculate the number of pennies to give the customer
    pennies = calculate_pennies(cents)
    cents = cents - pennies * 1

    # Sum coins
    coins = quarters + dimes + nickels + pennies

    # Print total number of coins to give the customer
    print(coins)

    # Print required coins
    print(quarters)
    print(dimes)
    print(nickels)
    print(pennies)


def get_cents():
    while True:
        cents_get = get_float("Change owed: ")
        if cents_get > 0:
            break

    cents_get = cents_get * 100
    return cents_get


def calculate_quarters(cents):
    q = 0
    if cents < 25:
        return q
    n = cents
    while n >= 25:
        q += 1
        n -= 25
    return q


def calculate_dimes(cents):
    d = 0
    if cents < 10:
        return d
    n = cents
    while n >= 10:
        d += 1
        n -= 10
    return d


def calculate_nickels(cents):
    ni = 0
    if cents < 5:
        return ni
    n = cents
    while n >= 5:
        ni += 1
        n -= 5
    return ni


def calculate_pennies(cents):
    p = 0
    if cents < 1:
        return p
    n = cents
    while n >= 1:
        p += 1
        n -= 1
    return p


main()