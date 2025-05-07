#include <cs50.h>
#include <math.h>
#include <stdio.h>

bool checkNumber(long number);
string checkForType(long number);

int main(void)
{
    // ask for number
    long number;
    do
    {
        number = get_long("Number: ");
    }
    while (number < 1);

    if (number < 1000000000000 || number > 9999999999999999)
    {
        printf("INVALID\n");
    }
    else
    {
        bool checksum = checkNumber(number);
        if (checksum)
        {
            string output = checkForType(number);
            printf("%s\n", output);
        }
        else
        {
            printf("INVALID\n");
        }
    }
}

// check if the checksum is correct
bool checkNumber(long number)
{
    int sum = 0;
    while (number) // as long as the number is not reduced to 0
    {
        int rest = number % 100;          // take 2 last digits
        int multiplied = (rest / 10) * 2; // take the most left and multiply by 2
        sum = sum + (multiplied / 10) +
              (multiplied % 10); // in case multiplied gives number > 9, this adds both digits to
                                 // the sum, instead of as a total

        rest = number % 10; // take last digit
        sum += rest;

        number = number / 100; // deletes last 2 digits
    }

    if ((sum % 10) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

string checkForType(long number)
{
    int length = 0;
    int firstTwoDigits;
    while (number)
    {
        number = number / 10;
        if (number > 9 && number < 100)
        {
            firstTwoDigits = number;
        }
        length++;
    }

    if (length == 13 || length == 16)
    {
        if ((firstTwoDigits / 10) == 4)
        {
            return "VISA";
        }
        else if (length == 16 && firstTwoDigits > 50 && firstTwoDigits < 56)
        {
            return "MASTERCARD";
        }
        else
        {
            return "INVALID";
        }
    }

    if (length == 15 && (firstTwoDigits == 34 || firstTwoDigits == 37))
    {
        return "AMEX";
    }
    else
    {
        return "INVALID";
    }
}
