#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Function to calculate sum
// Use 'toupper' method to handle case-sensitive comparisons
int calculateSum(string word, int values[])
{
    int sum = 0;
    int length = strlen(word);
    for (int i = 0; i < length; i++)
    {
        int currentChar = toupper(word[i]);

        // 'If' condition to check for only alphabet letters, both uppercase and lowercase letters
        // Calculate index of letter by substracting from position 'A'
        if ((currentChar >= 'A' && currentChar <= 'Z') ||
            (currentChar >= 'a' && currentChar <= 'z'))
        {
            int index = currentChar - 'A';
            sum += values[index];
        }
    }

    return sum;
}

int main(void)
{
    // Prompt the user for two words
    string player_1 = get_string("Player 1: ");
    string player_2 = get_string("Player 2: ");

    // Declare array of characters and assign numerical values

    char alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                         'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    int values[26] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                      1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

    // Compute the score for each word for both players
    int sum_player_1 = calculateSum(player_1, values);
    int sum_player_2 = calculateSum(player_2, values);

    // Determine the winner or if its a tie
    string winner;
    if (sum_player_1 > sum_player_2)
    {
        winner = "Player 1 wins!";
    }
    else if (sum_player_1 < sum_player_2)
    {
        winner = "Player 2 wins!";
    }
    else
    {
        winner = "It's a tie!";
    }

    // Print the winner

    printf("%s\n", winner);
}
