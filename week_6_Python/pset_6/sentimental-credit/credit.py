# TODO
from cs50 import get_int
from sys import exit


def main():
    number = get_int("Number: ")
    length = len(str(number))
    print(length)

    if length not in [13, 15, 16]:
        print("INVALID")
        exit(1)

    x = int(number)
    sum1 = 0
    sum2 = 0
    mod1 = 0
    mod2 = 0
    d1 = 0
    d2 = 0

    while True:
        mod1 = x % 10
        x = x // 10
        sum1 = sum1 + mod1

        #  remove second last digit
        mod2 = x % 10
        x = x // 10

        #  double second last digit and add individual digits to sum2
        mod2 = mod2 * 2
        d1 = mod2 % 10
        d2 = mod2 // 10
        sum2 = sum2 + d1 + d2

        if x <= 0:
            break

    total = sum1 + sum2

    # check Luhn Algorithm
    if total % 10 != 0:
        print("INVALID")
        exit(1)

    # get starting 2 digits
    start = number
    while True:
        start = start // 10
        if start < 100:
            break

    # check digits for card name
    if start // 10 == 5 and start % 10 in [1, 2, 3, 4, 5]:
        print("MASTERCARD")
    elif start // 10 == 3 and start % 10 in [4, 7]:
        print("AMEX")
    elif start // 10 == 4:
        print("VISA")
    else:
        print("INVALID")
        exit(1)


main()