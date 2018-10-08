from cs50 import get_string

def shift(case, char, key):

    # get ascii value of character
    ascii = ord(char)

    # determine casing
    casechar = 'a'
    if case == 1:
        casechar = 'A'

    # get alphabet spot
    abc_index = ascii - ord(casechar)

    # determine new place in alphabet
    shifted = (abc_index + key) % 26

    # return to ascii
    chasc= chr(shifted + (ord(casechar)))

    return chasc



# get user input frpm command line


# validate key and standardize
key = "bacon"
if not key.isalpha():
    print("Invalid key")

key.lower()

key_shifts = []
for i in range(len(key)):
    key_shift = ord(key[i]) - ord('a')
    key_shifts.append(key_shift)

# get plaintext
pltxt = get_string("plaintext: ")

# iterate over input
k = 0
for i in range(len(pltxt)):

    # if letter
    c = pltxt[i]
    if c.isalpha():

        if c.islower():
            c = shift(0, c, key_shifts[k % len(key_shifts)])
        else:
            c = shift(1, c, key_shifts[k % len(key_shifts)])

        k += 1

    print(c, end="")


