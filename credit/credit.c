#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    // Prompt the user to enter a credit card number
    long long cc, num;
    do
    {
        cc = get_long("Enter credit card number: ");
    }
    while (cc < 0);

    num = cc;

    // Calculat the total number of digits
    int count = (num == 0) ? 1 : (log10(num) + 1);
    int sum = 0;

    // Loop through each pair of digits of the credit card number
    while (num != 0)
    {
        // Extract the last digit (d1) and add it to sum
        int d1 = num % 10;
        sum += d1;

        // Extract the next-to-last digit (d2), double it, sum its digits (c1), and add them to sum
        int d2 = 2 * ((num / 10) % 10);
        int c1 = (d2 % 10) + floor((d2 / 10) % 10);
        sum += c1;

        // Remove the last two digits from the number
        num /= 100;
    }

    // Determine the card type based on the number of digits and starting digits
    string cardType;
    int test = cc / pow(10, count - 2);

    if ((count == 13 || count == 16) && test / 10 == 4)
    {
        cardType = "VISA";
    }
    else if (count == 16 && test >= 51 && test <= 55)
    {
        cardType = "MASTERCARD";
    }
    else if (count == 15 && (test == 34 || test == 37))
    {
        cardType = "AMEX";
    }
    else
    {
        cardType = "INVALID";
    }

    // Check if the sum is divisible by 10
    if (sum % 10 == 0)
    {
        printf("%s\n", cardType);
    }
    else
    {
        printf("INVALID\n");
    }
}
