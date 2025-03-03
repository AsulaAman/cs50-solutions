#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // declare variable "h" first
    int h;

    // assign value to variable "h"
    // make sure that "h" is between 1 and 8 (inclusive) by using || operator
    while ((h = get_int("Please enter a number between 1 and 8: ")) < 1 || h > 8)
    {
    }
    // first loop is for each row
    for (int i = 0; i < h; i++)
    {
        // second loop is for spaces on the left side
        for (int m = 0; m < h - i - 1; m++)
        {
            printf(" ");
        }

        // third loop is for the left side of hashes
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }

        // space to make a 2.gap between left and right side
        for (int s = 0; s < 2; s++)

        {
            printf(" ");
        }

        // fourth loop is for the right side of hashes
        for (int l = 0; l <= i; l++)
        {
            printf("#");
        }

        // move to the next line
        printf("\n");
    }
}
