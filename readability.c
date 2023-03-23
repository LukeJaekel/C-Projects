#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Function declarations
int amount_of_letters(string a);
int amount_of_words(string a);
int amount_of_sentences(string a);


int main(void)
{
    // Prompts user for string
    string text = get_string("Text: ");

    // String runs through functions
    int letters_result = amount_of_letters(text);
    int words_result = amount_of_words(text);
    int sentences_result = amount_of_sentences(text);

    // L is the average number of letters per 100 words
    double L = (double) letters_result / (double) words_result * 100;

    // S is the average number of sentences per 100 words
    double S = (double) sentences_result / (double) words_result * 100;

    // Combining the averages into The Coleman-Liau index formula
    double grade = 0.0588 * L - 0.296 * S - 15.8;
    int grade_rounded = (int)(grade < 0 ? (grade - 0.5) : (grade + 0.5));

    // Prints final result
    if (grade_rounded > 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade_rounded < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %d\n", grade_rounded);
    }

}


// Function that counts the amount of letters in the string excluding spaces (ASCII: 32)
int amount_of_letters(string a)
{
    int letters = 0;
    for (int i = 0; a[i]; i++)
    {
        if (a[i] != (a[i] < 31) && (a[i] > 63))

            letters++;

    }
    return letters;
}


// Function that counts the amount of words in the string excluding spaces (ASCII: 32)
int amount_of_words(string a)
{
    int words = 1;

    for (int i = 0; a[i]; i++)
    {
        if (a[i] == 32)

            words++;
    }
    return words;
}


// Function that counts the amount of sentences based on whether the symbols '!' (ASCII: 33), '?' (ASCII: 63) or '.' (ASCII: 46) are present
int amount_of_sentences(string a)
{
    int sentences = 0;

    for (int i = 0; a[i]; i++)
    {
        if (a[i] == 33 || a[i] == 46 || a[i] == 63)
        sentences++;

    }
    return sentences;
}
