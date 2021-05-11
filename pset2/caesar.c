#include <cs50.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Step 1 Counting Command Line-Arguments:  make agrv only accept 1 line of input, i.e. no "spaces or blank" (max 2 args only!).  If input entered correctly, print 'Success'. Else, re-prompt with 'Usage ./caesar key'.
// Step 2a Accessing the key: make argv only accept digits, reject other kind of chars to command line.
// Step 2b Validating the key: convert the string arg into integer. Use atoi function...
// Step 3: Prompt text input (Plaintext), then +1 to all chars and print the result(Ciphertext)


// 3a: Use the formula Ci = (pi + k) % 26 instead to recirculate 'z' to 'a'. Where Ci is i'th char of ciphertext, Pi is that of plaintxt, k is inputted key. Make sure casing remains the same!!!!!
// 3b: If string is alphabetic, shift plaintxt char by key, preserving the case(lower/uppercase). If it is not alphabet, preserve it as it is. Use functions isalpha, isupper, islower, and boolean case them.
// 3c: Use ACSII table to convert to alphabet index digits. General formula as used in scrabble was something like --> char c = 'A' +1;
// 3d: Convert back to ACSII alphabetical chars.


int main (int argc, string argv[]){

//Part 1: Prompting the user a number input to the command line after ./caesar

    if (argc == 2 )
    {
        int stringtoints = atoi (argv[1]); //atoi converts user's string number input to actual int number
        printf("%i\n", stringtoints);

        for (int i = 0, n = strlen(argv[1]); i < n ; i++)
        {
            if (isdigit(argv[1][i]) == false) //if any character is not a digit, then return back to Part 1 prompt (this).
            {
                printf("Usage ./caesar key\n");
                return 1;
            }
        }
        printf("Success!\n");

//Part 2: Get user's text input and ciphering this text

        string plaintext = get_string ("plaintext: \n"); // Get user's input for the plaintext
        printf("ciphertext: ");

            for (int i = 0, n = strlen(plaintext); i < n ; i ++) // Go through each char in the plaintext string
            {
                if (isalpha(plaintext[i]) && islower(plaintext[i])) // If the char is lower case,
                {

                    char cipherchar = (((plaintext[i] + stringtoints - 97) % 26) + 97); // Then create a newly ciphered char by adding the user's desired number input earlier on. Number 97 corresponds to lowercase ACSII
                    printf("%c", cipherchar);
                }

                else if (isalpha(plaintext[i]) && isupper(plaintext[i])) // if the char is upper case,
                {
                    char cipherchar = (((plaintext[i] + stringtoints -65 ) % 26) + 65);  // Then create a newly ciphered char by adding the user's desired number input earlier on. Number 97 corresponds to uppercase ACSII
                    printf("%c", cipherchar);
                }

                else
                {
                    printf("%c", plaintext[i]); // Prints all the punctuation marks and whatnot.
                }

            }

        printf("\n");

    }

// Part 1.5: Failure to key in positive integers without any spacing
    else
    {
        printf("Usage ./caesar key\n");
        return 1;
    }

}
