from cs50 import get_int, get_string
import re

def main():
    number = get_string("Number: ")
    match = re.search(r"^\d{13,16}$", number)
    if not match:
        print("INVALID")
        return 1

    number = int(number)
    checksum = checkNumber(number)
    if checksum:
        output = checkForType(number)
        print(f"{output}")
    else:
        print("INVALID")


def checkNumber(n):
    sum = 0
    while n != 0:
        rest = n % 100
        multiplied = int(rest / 10) * 2
        sum = int(sum + int(multiplied / 10) + (multiplied % 10))

        rest = n % 10
        sum += rest

        n = int(n / 100)
        
    if (sum % 10) == 0:
        return True
    else:
        return False


def checkForType(n):
    length = 0
    firstTwoDigits = 0
    while n:
        n = int(n / 10)
        if n > 9 and n < 100:
            firstTwoDigits = n
        length += 1;

    if length == 13 or length == 16:
        if int((firstTwoDigits / 10)) == 4:
            return "VISA"
        elif length == 16 and firstTwoDigits > 50 and firstTwoDigits < 56:
            return "MASTERCARD"
        else:
            return "INVALID"

    if length == 15 and (firstTwoDigits == 34 or firstTwoDigits == 37):
        return "AMEX"
    else:
        return "INVALID"


main()
