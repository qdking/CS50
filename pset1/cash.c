#include <cs50.h>
#include <stdio.h>
#include <math.h>

//American coins: 25c, 10c, 5c, 1c

int main(void)
{
// Declaring the variables
float cash;
int variable = 0; //int variable is the number of times there is a change

// Prompt the user's input for the money he/she wants to change until it is a positive number
do
    {cash = get_float("Gimme your money!\n");
    printf("Change owned: %0.2f\n", cash);
    }
while (cash <= 0);

// Eliminates the decimal number from the float cash as Integer c
int c = round(cash * 100);

// Grand loop starts
while (c - 25 >= 0) //minus all 25cents possible
   {c = c - 25;
    variable++;
   }

{while (c - 10 >= 0) //minus all 10cents possible
   {c = c - 10;
    variable++;
   }

while (c - 5 >= 0) //minus all 5cents possible
   {c = c - 5;
    variable++;
   }

while (c - 1 >= 0) //minus all 1cents possible
   {c = c - 1;
    variable++;
   }

printf("%i\n", variable);
}
}
