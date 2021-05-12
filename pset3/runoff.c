#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Max voters and candidates - Defined by our dear CS50 instructors - Please save me! Help! Save me from depression.
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// Declaring array for preferences[i][j] is jth preference for voter i (i is the voter index)(j is the preference ranking number).
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Structure of the Candidates' Scoring Status - Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

// START of commandline main method
// Check for invalid usage - Reject single argument because No. of candidates must be 2 or more
int main(int argc, string argv[])
{
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates (Defining the no. of candidates as no.of arguments received - 1)
    candidate_count = argc - 1;

    // Reject any number greater than 9 as defined by the scope of this assignment.
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }

    // Declaring the initial candidate's vote count and the elimination status of each candidate.
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    // Set how many voters you want there to be. Reject if it is more than 100, as defined by the scope of this assignment.
    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // VOTING STARTS, Voter's input: Prompting voters for for their choices for each ranking.
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)  // Query for each ranking preferences
        {
            string name = get_string("Rank %i: ", (j + 1)); // Rank 1 = ... Rank 2 = ... so on and so forth until Rank j+1 (Rank "Last No. of Candidate")

            if (!vote(i, j, name))  // (****** VOTE FUNCTION ******) Record vote, unless it is invalid aka if vote(i,j, name) is false
            {
                printf("Invalid vote.\n");
                return 4; //Return to this 4th function in int main()
            }
        }

        printf("\n");
    }
    // VOTING ENDS

    // Keep holding runoffs until winner exists - i.e. While all inputs were true (none of the return 1-4), then do the following:
    while (true)
    {
        // Calculate votes given remaining candidates (*TABULATE SCORES FUNCTION*)
        tabulate();

        // Check if election has been won (*PRINT THE WINNER FUNCTION*)
        bool won = print_winner();
        if (won)
        {
            break; //break to stop all other possible actions
        }

        // Eliminates last-place candidates (*FIND THE MIN SCORE FUNCTION, CHECK WHO TIED FUNCTION, ALSO THE ELIMINATE FUNCTION*)
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name); //Prints the candindates who tied and were not eliminated
                }
            }
            break;
        }

        // Eliminates anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero - After eliminating, set that candidate's vote count to zero.
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0; //return logic flow to this main method starting from line 96 bool won = print_winner();
}
// END OF THE MAIN METHOD

// VOTE FUNCTION: Record voters' preferences input if their vote input is valid. PREFERENCE[I][J]: Have to go through each voter [i] and each voter's ranking [j]
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0) // Get String for name, and check if this name is existing by using string compare strcmp(name name) = true (i.e. == 0)
        {
            preferences[voter][rank] = i;     // If strcmp is true, then use this string to get the candidate's int number i in candidate[i].
            return true;
        }
    }
    return false;
}
// VOTE FUNCTIONS ENDS

// TABULATE FUNCTIONS STARTS: TOTAL UP votes for all non-eliminated candidates
void tabulate(void) // Used in Line 95
{
    // 1. Recall that voter_count stores the number of voters in the election.
    // 2. Recall that for a voter i, their top choice candidate is represented by preferences[i][0], their second choice candidate by preferences[i][1], etc.
    // 3. Recall that the candidate struct has a field called eliminated, which will be true if the candidate has been eliminated from the election. // candidates[i].name = argv[i + 1]; // candidates[i].votes = 0; // candidates[i].eliminated = false;
    // 4. Recall that the candidate struct has a field called votes, which you’ll likely want to update for each voter’s preferred candidate.

    for (int i = 0; i < voter_count; i++) //  Go through each voter's preference[i][j] = X
    {
        int j = 0;

        if (candidates[preferences[i][j]].eliminated == false)  // If 1st ranking was not eliminated, count vote for 1st ranking
        {
            candidates[preferences[i][j]].votes++;
        }

        else if (candidates[preferences[i][j]].eliminated == true)  // If 1st ranking was eliminated
        {
            for (j = 1; j < candidate_count; j++) // Increase ranking until there is a ranking that wasn't eliminated yet, and count it.
            {
                if (candidates[preferences[i][j]].eliminated == false)
                {
                    candidates[preferences[i][j]].votes++;
                    break;
                }
            }
        }
    }
    return;
}


// TABULATE FUNCTION ENDS

// PRINT WINNER FUNCTION starts: Print the winner of the election, if there is one
bool print_winner(void)
{
    // 1. If any candidate has more than half of the vote, their name should be printed to stdout and the function should return true.
    // 2. If nobody has won the election yet, the function should return false.
    // 3. Recall that voter_count stores the number of voters in the election. Given that, how would you express the number of votes needed to win the election?

    // int rounded_voter_count = round(voter_count/2);
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > (voter_count/2)) // If this candidate's vote covers the majority vote population, then there is a sole winner found
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}
// END OF PRINT-WINNER FUNCTION

// FIND MIN FUNCTION STARTS: Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // 1. The function should return the minimum vote total for any candidate who is still in the election.
    // 2. You’ll likely want to loop through the candidates to find the one who is both still in the election and has the fewest number of votes. What information should you keep track of as you loop through the candidates?

    int min = 1;
    int growing_number = 0;
    int i;
    bool min_found;

    do
    {
        growing_number++;

        for (i = 0; i < candidate_count; i++)
        {
            if (candidates[i].eliminated == false && candidates[i].votes - growing_number == 0)
            {
                min = candidates[i].votes;
                min_found = true;
            }
        }
    }
    while (min_found == false);

    return min;
}
// END OF FIND MIN FUNCTION.

// TIE INDICATOR FUNCTION
// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // 1. The function takes an argument min, which will be the minimum number of votes that anyone in the election currently has.
    // 2. The function should return true if every candidate remaining in the election has the same number of votes, and should return false otherwise.
    // 3. Recall that a tie happens if every candidate still in the election has the same number of votes. Note, too, that the is_tie function takes an argument min
    //    which is the smallest number of votes any candidate currently has. How might you use that information to determine if the election is a tie (or, conversely, not a tie)?

    for (int i = 0 ; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false && candidates[i].votes != min)
        {
            return false;
        }
    }
    return true;

}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // 1. The function takes an argument min, which will be the minimum number of votes that anyone in the election currently has.
    // 2. The function should eliminate the candidate (or candidates) who have min number of votes.

    for (int i = 0 ; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }

    return;
}
