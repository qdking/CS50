#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count (The structure)
typedef struct
{
    string name;
    int votes;
}
candidate;
// End of struct

// Declaring an Array of candidates
candidate candidates[MAX];

// Declaring the Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

// Main method command
int main(int argc, string argv[])
{
    // Check for invalid usage (no user input after the command ./plurality)
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates (Number of candidates cannot exceed 9)
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    // Opening up an array for all the candidates, including their elements (structs): their names, and their votes to be obtained
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1]; // argv start from i+1 because i + 1 = 1
        candidates[i].votes = 0; // candidate votes start from 0.
    }

    // Prompt user's input for number of voters
    int voter_count = get_int("Number of voters: ");

    // Loop over all voters [i]: Using the function vote(name) (Voters to choose the candidate)
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Function with parameter string name: Update total votes given a new vote (done)

bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0) //compare strings of candidate's names earlier on vs name voted by voter, == 0 if true
        {
            candidates[i].votes ++;
            return true;
        }
    }
    return false;
}

// Tabulate all scores and Print the winner(s) of the election (MAJORITY OF HOMEWORK PORTION)

void print_winner(void)
{
// Start of selection sort loop
    int temporalint;
    string temporalstring;
    int tie = candidate_count - 1; // a Tie counter, checks if a candidate vote is equal to every other candidate's vote, 1 by 1
    int truthcounter = 0; // Just an int counter for later
    int wincounter = 0; // Just an int counter for later

    for (int i = 0; i < candidate_count - 1; i++) // Sorting all candidates (name and vote) in ascending order according to the number of votes they've gotten
    {
        if (candidates[i].votes > candidates[i + 1].votes)
        {
            temporalint = candidates[i].votes;
            temporalstring = candidates[i].name;
            candidates[i].votes = candidates[i + 1].votes;
            candidates[i].name = candidates[i + 1].name;
            candidates[i + 1].votes = temporalint;
            candidates[i + 1].name = temporalstring;
        }
    }

// End of a selection sort loop

// To decide the winner:
    do
    {
        if (candidates[candidate_count - 1].votes > candidates[candidate_count - 1 - truthcounter].votes) // If the final position candidate has greater votes than the 2nd last, 3rd last... position candidate's vote,
        {
            wincounter ++; //+1 score point to victory
        }
        truthcounter ++;
    }
    while (truthcounter <= candidate_count - 1);

    if (wincounter == truthcounter) // If wincounter and truthcounter were both equally successfully looped, this means every last checked candidate has more votes than the one in front, therefore we print its name.
    {
        printf("%s\n", candidates[candidate_count - 1].name); //Print the sole winner's name
    }

// To see if who tied:
    do
    {
        if ((candidates[candidate_count - 1].votes) == (candidates[candidate_count - 1 - tie].votes)) //If last position votes == 1st position's votes, 2nd positions votes, 3rd position's votes and so on (loops further)
        {
            printf("%s\n", candidates[candidate_count - 1 - tie].name); // Then print the tied candidate's name 1 by 1.
        }
        tie--; // int tie = candidate_count - 1
    }
    while (tie >= 0);

    return; //(to return flow in the main void method)
}


