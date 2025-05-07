from cs50 import get_string
import re

def main():
    text = get_string("Text: ")

    punctuations = calculatePunct(text)
    words = calculateWords(text)
    letters = calcularteLetters(text)

    # Calculate the average letters and sentences per 100 words
    averageLetters = (letters / words) * 100
    averageSentences = (punctuations / words) * 100

    # Apply formula
    formula = (0.0588 * averageLetters) - (0.296 * averageSentences) - 15.8

    if formula < 1.0:
        print("Before Grade 1")
    elif formula > 16.0:
        print("Grade 16+")
    else:
        print(f"Grade {round(formula)}")


def calculatePunct(text):
    list = re.findall(r"[!\.\?]", text)
    return len(list)


def calculateWords(text):
    list = re.findall(" ", text)
    return len(list) + 1


def calcularteLetters(text):
    list = re.findall(r"[a-zA-Z]", text)
    return len(list)

main()
