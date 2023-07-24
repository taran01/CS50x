# TODO
from cs50 import get_string


def main():
    # Get user input
    text = get_string("Text: ")
    if len(text) < 1:
        exit(1)

    letters = count_letters(text)
    print(f"letters: {letters}")

    words = count_words(text)
    print(f"words: {words}")

    sentences = count_sentences(text)
    print(f"sentences: {sentences}")

    #  Calculate L & S
    L = letters / words * 100
    S = sentences / words * 100

    # Computing Coleman-Liau index
    index = 0.0588 * L - 0.296 * S - 15.8

    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {round(index)}")


# Function to count letters
def count_letters(text):
    ltrs = 0
    for i in range(0, len(text)):
        if text[i].isalpha():
            ltrs += 1
    return ltrs


# Function to count words
def count_words(text):
    wrds = 1
    if len(text) < 1:
        wrds = 0
        return wrds

    for i in range(0, len(text)):
        if text[i] == " ":
            wrds += 1

    return wrds


# Function to count sentences
def count_sentences(text):
    stencs = 0
    for i in range(0, len(text)):
        if text[i] in [".", "?", "!"]:
            stencs += 1

    return stencs


main()