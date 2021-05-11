#include <cs50.h>
#include <stdio.h>

int main(void)

{

// Declare h as height of the mario pyramid
int h;

// Prompt for user's height input is incorrect
    do {
        h = get_int("Height? (Enter between 0 and 9): ");
       }
    while (h < 1 || h > 8);


// If user's height input is correct, then
    if (h > 1 || h < 9){

        int variable = 0;

// Grand loop
// For o determines number of "\n aka rows and "o-1" will produce "h-1", and do "2-4" bricks instead of "1-3" bricks when h= 3.
// i determines no. of "#" that increases along with "variable" for each single loop count.
    {
     for (int o = 0; o < h; o++){

            // Inner loop
             for (int space = h ; space - 1 >= variable; space--){ //Prints no. of spaces needed at the top, then the number of spaces decrease as it loops down
                if (space != h){
                     printf(" ");
                 }
            }

        // 2nd inner loop on the same level
        {
            for(int i = 0; i <= variable; i++) //Prints no. of # needed at at the top, then the number of # increases as it loops down
                printf("#");
        }
    printf("\n"); // For each grand loop, print a \n to go over to the new line

    variable++; // For each variable, create a new grand loop for a new line
    }

    }}

}







