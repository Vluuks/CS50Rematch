from cs50 import get_int

# get user input
height = 0
while height > 26 or height < 1:
    height = get_int("Heigth:")

# build pyramid
for i in range(height) :

    # spaces
    for j in range(height - i):
        print("-", end="")

    # hashes left
    for k in range(i + 2):
        print("#", end="")

    # middle
    print("--", end="")

    # hashes right
    for l in range(i + 2):
        print("#", end="")

    # newline
    print("")
