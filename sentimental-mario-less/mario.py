from cs50 import get_int


def half_pyramid(height):
    for i in range(1, height + 1):
        # Print spaces in pyramid first ensuring they are aligned to the left then number of hashes
        print(' ' * (height - i) + '#' * i)


# Ask user for the height of the pyramid
height = 0
while True:
    try:
        height = int(input("Height: "))  # input an integer
        # Check if its within the range
        if 1 <= height <= 8:
            break  # Exit if valid
        else:
            print("Please enter a number between 1 and 8")
    except ValueError:
        print("Invalid")

# Call function to print out the hashes
half_pyramid(height)
