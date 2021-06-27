from cs50 import get_float, get_int, get_string

# Prompts user to enter text, and calculate its readbility using the formula, and printf this number.
# Formula: index = 0.0588 * L - 0.296 * S - 15.8.
# L is the average number of letters per 100 words in the text.
# S is the average number of sentences (no. of punctuatutions) per 100 words in the text.
# W is the no. of words per 100 words (= no. of spaces/100).

# Step 1: Prompt user for string text.
# Step 2: String is an array of chars. Use this array.
# Step 3a: if string array integer is within cetain value (aka a-Z array value), +1 integer counter x, calculate float L = x/(W/100).
# Step 3b: if string array integer has specific space's value (aka no. of sentences), + integer counter y, calculate float S = y/(W/100).
# Step 4: calculate float Formula = 0.0588* L - 0.296 * S - 15.8. If value < ?? print ???. Else print ???

# String is an array of chars. Testing to print this out:
#printf("Your input were %c %c %c\n", usertext[0],usertext[1],usertext[2]);

# // Declaring variables

Letters = 0
Words = 0
Sentences = 0

# // Prompting user's input for the words and sentences.
usertext = get_string("Input your text here\n")

# // Letters counting loop counter
for i in range(len(usertext)):
    if usertext[i].lower() >= 'a' and usertext[i].lower() <= 'z':
        Letters += 1

# // Word counting loop counter, defined by number of spaces there are.
for i in range(len(usertext)):
    if usertext[i] == ' ':
        Words += 1

# // Sentences counting loop counter
for i in range(len(usertext)):
    if usertext[i] == '.' or usertext[i] == '!' or usertext[i] == '?':
        Sentences += 1

# // Calculate L from Letters and S from Sentences. Calculate Index from L, S and W. L = x/(W/100). S = y/(W/100). Index = 0.0588 * L - 0.296 * S - 15.8.
W = Words + 1
L = Letters * 100.00 / W
S = Sentences * 100.00 / W
Index = round(0.0588 * L - 0.296 * S - 15.8)

# // Grade output
if Index < 1:
    print("Before Grade 1")

elif Index >= 16:
    print("Grade 16+")

else:
    print("Grade " + str(Index))
