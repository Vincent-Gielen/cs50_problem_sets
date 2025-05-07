#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int doChecks(string key);
string makeCipher(string plaintext, int length, string key);

int main(int argc, string argv[])
{
    // check if the correct amount of keys was passed (1)
    if (argc != 2)
    {
        printf("You should pass along exactly 1 command-line argument\n");
        return 1;
    }

    // store the given key
    string key = argv[1];

    // do all other checks involving key
    int failCode = doChecks(key);
    if (failCode != 0)
    {
        return 1;
    }

    // ask for plaintext
    string plaintext = get_string("plaintext: ");
    int length = strlen(plaintext);

    string ciphertext = makeCipher(plaintext, length, key);
    printf("ciphertext: %s\n", ciphertext);
}

int doChecks(string key)
{
    // check if the length of the key is 26 characters
    if (strlen(key) != 26)
    {
        printf("The length of the key must be 26 characters\n");
        return 1;
    }

    // check if every character is a letter
    for (int i = 0; i < 26; i++)
    {
        if (isalpha(key[i]) == 0)
        {
            printf("The key must contain only alphabetical characters\n");
            return 1;
        }

        // check for repeating characters
        for (int j = 0; j < i; j++)
        {
            if (toupper(key[i]) == toupper(key[j]))
            {
                printf("They key must not contain repeated characters\n");
                return 1;
            }
        }
    }
    return 0;
}

string makeCipher(string plaintext, int length, string key)
{
    string ciphertext = plaintext;

    for (int i = 0, n = length; i < n; i++)
    {
        char letter = plaintext[i];

        if (isalpha(letter) != 0)
        {
            // check if the letter is uppercase
            int isUppercase = isupper(letter);
            // define ascii value of letter and substract it by correct amount based on if the
            // letter is upper- or lowercase to make it 0-based
            int indexOfChar;
            if (isUppercase == 0)
            {
                indexOfChar = letter - 97;
            }
            else
            {
                indexOfChar = letter - 65;
            }

            char newLetter;
            for (int j = 0; j < 26; j++)
            {
                if (indexOfChar == j)
                {
                    newLetter = key[j];
                    break;
                }
            }

            if (isUppercase != 0)
            {
                newLetter = toupper(newLetter);
            }
            else
            {
                newLetter = tolower(newLetter);
            }

            ciphertext[i] = newLetter;
        }
        else
        {
            ciphertext[i] = letter;
        }
    }
    return ciphertext;
}
