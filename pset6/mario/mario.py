from cs50 import get_float, get_int, get_string

# Declaration of variables
h = 0
variable = 0

# Prompt for user's height input is incorrect
while h < 1 or h > 8:
    h = get_int("Choose an integer between 0 and 9 for the height: ")

# # Grand loop
for floor in range(h):

    # 1st inner loop to print spaces
    for space in range(h, variable, -1):
        if space != h:
            print(" ", end="")

    # 2nd inner loop to print hexes
    for hexes in range(variable + 1):
        print("#", end="")

    # Thereafter, print \n to a new line row
    print("")
    variable += 1
