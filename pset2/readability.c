#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

// Prompts user to enter text, and calculate its readbility using the formula, and printf this number.
// Formula: index = 0.0588 * L - 0.296 * S - 15.8.
// L is the average number of letters per 100 words in the text.
// S is the average number of sentences (no. of punctuatutions) per 100 words in the text.
// W is the no. of words per 100 words (= no. of spaces/100).

// Step 1: Prompt user for string text.
// Step 2: String is an array of chars. Use this array.
// Step 3a: if string array integer is within cetain value (aka a-Z array value), +1 integer counter x, calculate float L = x/(W/100).
// Step 3b: if string array integer has specific space's value (aka no. of sentences), + integer counter y, calculate float S = y/(W/100).
// Step 4: calculate float Formula = 0.0588* L - 0.296 * S - 15.8. If value < ?? print ???. Else print ???

// String is an array of chars. Testing to print this out:
//printf("Your input were %c %c %c\n", usertext[0],usertext[1],usertext[2]);

int main(void)
{
// Declaring variables

    int Letters = 0;
    int Words = 0;
    int Sentences = 0;

// Prompting user's input for the words and sentences.
    string usertext = get_string("Input your text here\n");

// Letters counting loop counter

    for (int i = 0, n = strlen(usertext); i < n; i++)
    {
        if (usertext[i] >= 'a' && usertext[i] <= 'z') // usertext string itself is an array. No need to convert them into numbers, can directly use alphabets 'a' and 'z'.
        {
            Letters++;
        }

        if (usertext[i] >= 'A' && usertext[i] <= 'Z')
        {
            Letters++;
        }
    }

// Word counting loop counter
    for (int x = 0, n = strlen(usertext); x < n; x++)
    {
        if (usertext[x] == ' ') // Word is defined by number of spaces there are.
        {
            Words++;
        }
    }


// Sentences counting loop counter
    for (int y = 0, n = strlen(usertext); y < n; y++)
    {
        if (usertext [y] == '.' || usertext [y] == '!' || usertext [y] == '?') // Sentence is defined by the number of these 3 punctuations there are.
        {
            Sentences++;
        }
    }


// Calculate L from Letters and S from Sentences. Calculate Index from L, S and W. L = x/(W/100). S = y/(W/100). Index = 0.0588 * L - 0.296 * S - 15.8.

    int W = Words + 1;
    float L = Letters * 100.00 / W;
    float S = Sentences * 100.00 / W;
    int Index = round(0.0588 * L - 0.296 * S - 15.8);


// Grade output
    if (Index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (Index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", Index);
    }
}
