from cs50 import get_float, get_int, get_string

# Declaring the variables
# variable is the number of times there is a change
cash = 0.00
variable = 0

# Prompt the user's input for the money he/she wants to change until it is a positive number
while cash <= 0:
    cash = get_float("Gimme your money!\n")
    print("Change owed: " + str(cash))

# Eliminates the decimal number from the float cash as Integer c
c = round(cash * 100)

#minus all 25 cents possible
while c - 25 >= 0:
    c -= 25
    variable += 1

#minus all 10 cents possible
while c - 10 >= 0:
    c -= 10
    variable += 1

#minus all 5 cents possible
while c - 5 >= 0:
    c -= 5
    variable += 1

#minus all 1 cents possible
while c - 1 >= 0:
    c -= 1
    variable += 1

print(variable)
