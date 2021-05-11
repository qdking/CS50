#include <cs50.h>
#include <stdio.h>
#include <math.h>

//American coins: 25c, 10c, 5c, 1c

int main(void)
{
float cash;
int variable = 0;

//prompt
do
    {cash = get_float("Gimme your money!\n");
    printf("Change owned: %0.2f\n", cash);
    }
    while (cash <= 0);
//grand loop

int c = round(cash * 100);

while (c - 25 >= 0)
   {c = c - 25;
    variable++;
   }

{while (c - 10 >= 0)
   {c = c - 10;
    variable++;
   }

while (c - 5 >= 0)
   {c = c - 5;
    variable++;
   }

while (c - 1 >= 0)
   {c = c - 1;
    variable++;
   }

printf("%i\n", variable);
}
}
