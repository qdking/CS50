// Simulate genetic inheritance of blood type

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles (STRUCT DONE)
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

//  CONSTANTS DECLARED IN THE PSET SCENARIO
const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

// DECLARE ALL FUNCTIONS USED FOR MAIN VOID
person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void) //(!!!!!!!!!!!!!!!!       MAIN VOID METHOD DONE            !!!!!!!!!!!!!!!!!!!!)
{
    // Seed random number generator (PSEUDO RANDOM NUMBER GENERATOR FOR RANDOM ALLELE FUNCTION BELOW)
    srand(time(0));

    // Create a new family with three generations (FAMILY CREATION FUNCTION DONE)
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types (PRINTING OUT RESULTS DONE)
    print_family(p, 0);

    // Free memory (FREE FUNCTION DONE)
    free_family(p);
}

// Create a new individual with `generations` (FAMILY CREATION FUNCTION)
person *create_family(int generations)
{
    // TODO: Allocate memory for new person
    person *p = malloc(sizeof(person));
    if (p == NULL)
    {
        return 0;
    }

    // Generation with parent data (RECURSIVE CASE)
    if (generations > 1)
    {
        // TODO: Recursively create blood type histories for parents

        p -> parents[0] = create_family(generations - 1);
        p -> parents[1] = create_family(generations - 1);

        // TODO: Randomly assign child alleles based on parents

        p -> alleles[0] = p -> parents[0] -> alleles[rand() % 2];
        p -> alleles[1] = p -> parents[1] -> alleles[rand() % 2];
    }

    // Generation without parent data (BASE CASE: (generation 0 ?))
    else
    {
        // TODO: Set parent pointers to NULL
        p -> parents[0] = NULL;
        p -> parents[1] = NULL;
        // TODO: Randomly assign alleles

        p -> alleles[0] = random_allele();
        p -> alleles[1] = random_allele();
    }

    // TODO: Return newly created person

    // return person;

    return p;
}

// Free `p` and all ancestors of `p`. (RECURSION)
void free_family(person *p)
{

    // TODO: Handle base case (If NULL, you should never be freeing a pointer)
    if (p == NULL)
    {
        return;
    }

    // TODO: Free parents (RECURSIVELY FREEING THE PARENTS: CALL THE FREE FAMILY FUNCTION ON EACH PARENTS, WHICH WILL ALSO CALL THE GRANDPARENTS..)

    free_family(p -> parents[0]);
    free_family(p -> parents[1]);

    // TODO: Free child
    free(p);
    // if base case..
    // else..
}

// Print each family member and their alleles. (DONE)
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation (DONE)
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person (DONE)
    printf("Generation %i, blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele. (DONE)
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
