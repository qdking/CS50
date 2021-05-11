#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Game Points assigned to each letter of the alphabet
int POINTS[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
//                a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p   q  r  s  t u   v  w  x   y  z


int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    printf("score 1 is %i, score 2 is %i. \n", score1, score2);
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }

}

// Compute score function, with the parameter string word
int compute_score(string word)
{

    int totalscore = 0;

    // TODO: Compute and return score for string
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        char helpme = tolower(word[i]);
        if (isalpha(helpme) != 0 )
        {
            totalscore += POINTS[(helpme - 97)];
        }
    }
    return totalscore;
}

            // Identify each char in the word1 string array. Convert it to their respective ACSII number? Tag this number to POINTS[number] array and add up together?!
            // Change all uppercase to lowercase?
            // '97' to '122' represents a to z. Since 'a''s identity is at int POINT[0], 'b' is int POINT[1], can we use 97-97=0, 98-97=1...?
