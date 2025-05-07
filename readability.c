#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int calculatePunct(string text);
int calculateWords(string text);
int calculateLetters(string text);

int main(void)
{
    string text = get_string("Text: ");

    int punctuations = calculatePunct(text);
    int words = calculateWords(text);
    int letters = calculateLetters(text);
    // calculate the average letters and sentences per 100 words
    double averageLetters = ((double) letters / words) * 100;
    double averageSentences = ((double) punctuations / words) * 100;

    // apply the given formula
    double formula = (0.0588 * averageLetters) - (0.296 * averageSentences) - 15.8;

    if (formula < 1.0)// if the grade is below 1
    {
        printf("Before Grade 1\n");
    }
    else if (formula > 16.0)// if the grade is above 16
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(formula));// round it to the nearest int
    }
}

// calculate the amount of punctuation marks(.!?) in the text
int calculatePunct(string text)
{
    int sum = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sum++;
        }
    }
    return sum;
}

// calculate the amount of words( word ) in the text
int calculateWords(string text)
{
    int sum = 1;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            sum++;
        }
    }
    return sum;
}

// calculate the amount of letters(a-z&A-Z) in the text
int calculateLetters(string text)
{
    int sum = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char symbol = text[i];
        if (isalpha(symbol) != 0)
        {
            sum++;
        }
    }
    return sum;
}
